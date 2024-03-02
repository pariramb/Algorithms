#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  struct Parameters {
    int weight;
    int from;
    int to;
    Parameters() = default;
    Parameters(int weight, int from, int to) : weight(weight), from(from), to(to) {
    }
  };
  std::vector<Parameters> graph_;
  int count_vertex_;
  int count_edges_;

 public:
  Graph(int count_vertex, int count_edges);
  int Kruskal();
  //   friend bool Compare(const Parameters&, const Parameters&);
};

class DisjointSetUnion {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  int count_sets_;

 public:
  void MakeSet(const int&);
  int FindSet(const int&);
  void Union(const int&, const int&);
};

void DisjointSetUnion::MakeSet(const int& count_sets) {
  count_sets_ = count_sets;
  parent_.reserve(count_sets_);
  rank_.resize(count_sets_, 1);
  for (int i = 0; i < count_sets_; ++i) {
    parent_[i] = i;
  }
}

int DisjointSetUnion::FindSet(const int& element) {
  if (element == parent_[element]) {
    return element;
  }
  return parent_[element] = FindSet(parent_[element]);
}

void DisjointSetUnion::Union(const int& element1, const int& element2) {
  int root1 = FindSet(element1);
  int root2 = FindSet(element2);
  if (root1 != root2) {
    --count_sets_;
    if (rank_[root1] < rank_[root2]) {
      parent_[root1] = root2;
    } else if (rank_[root2] < rank_[root1]) {
      parent_[root2] = root1;
    } else {
      parent_[root1] = root2;
      rank_[root2] += 1;
    }
  }
}

Graph::Graph(int count_vertex, int count_edges) : count_vertex_(count_vertex), count_edges_(count_edges) {
  int from = 0;
  int to = 0;
  int weight = 0;
  graph_.reserve(count_edges_ + 1);
  for (int i = 1; i < count_edges_ + 1; ++i) {
    std::cin >> from >> to >> weight;
    graph_.emplace_back(weight, from, to);
  }
}

// bool Compare(const Graph::Parameters& first, const Graph::Parameters& second) {
//   return (first.weight < second.weight);
// }

int Graph::Kruskal() {
  int weight = 0;
  //   std::sort(graph_.begin(), graph_.end(), Compare);
  DisjointSetUnion trees;
  trees.MakeSet(count_vertex_ + 1);
  for (auto edge : graph_) {
    if (trees.FindSet(edge.from) != trees.FindSet(edge.to)) {
      trees.Union(edge.from, edge.to);
      weight += edge.weight;
    }
  }
  return weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int count_vertex = 0;
  int count_edges = 0;
  std::cin >> count_vertex >> count_edges;
  Graph graph(count_vertex, count_edges);
  std::cout << graph.Kruskal();
  return 0;
}
