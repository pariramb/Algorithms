#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  struct Parameters {
    int weight_or_dist;
    int vertex;
    Parameters(int weight, int vertex) : weight_or_dist(weight), vertex(vertex) {
    }
  };
  std::vector<std::vector<Parameters>> graph_;
  size_t count_vertex_;
  size_t count_edges_;

 public:
  Graph(size_t count_vertex, size_t count_edges);
  int Prim();
  friend struct Compare;
};

struct Compare {
  bool operator()(const Graph::Parameters& first, const Graph::Parameters& second) {
    return first.weight_or_dist > second.weight_or_dist;
  }
};

int Graph::Prim() {
  const int64_t inf = INT64_MAX;
  const int64_t none = -1;
  int weight = 0;
  std::vector<bool> is_used(count_vertex_ + 1, false);
  std::vector<int64_t> dist(count_vertex_ + 1, inf);
  dist[1] = 0;
  is_used[1] = true;
  std::vector<int> prev(count_vertex_ + 1, none);
  std::priority_queue<Parameters, std::vector<Parameters>, Compare> possible_candidates;
  possible_candidates.emplace(0, 1);
  while (!possible_candidates.empty()) {
    auto vertex = possible_candidates.top();
    possible_candidates.pop();
    if (!is_used[vertex.vertex]) {
      weight += vertex.weight_or_dist;
    }
    is_used[vertex.vertex] = true;
    for (auto it : graph_[vertex.vertex]) {
      if ((!is_used[it.vertex]) && (it.weight_or_dist < dist[it.vertex])) {
        prev[it.vertex] = vertex.vertex;
        dist[it.vertex] = it.weight_or_dist;
        possible_candidates.emplace(it);
      }
    }
  }
  return weight;
}

Graph::Graph(size_t count_vertex, size_t count_edges) : count_vertex_(count_vertex), count_edges_(count_edges) {
  int vertex1 = 0;
  int vertex2 = 0;
  int weight = 0;
  graph_.resize(count_vertex_ + 1);
  for (size_t i = 1; i < count_edges_ + 1; ++i) {
    std::cin >> vertex1 >> vertex2 >> weight;
    graph_[vertex1].emplace_back(weight, vertex2);
    graph_[vertex2].emplace_back(weight, vertex1);
  }
}

int main() {
  size_t count_islands = 0;
  size_t count_bridges = 0;
  std::cin >> count_islands >> count_bridges;
  Graph graph(count_islands, count_bridges);
  std::cout << graph.Prim();
  return 0;
}
