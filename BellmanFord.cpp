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
  size_t count_vertex_;
  size_t count_edges_;
  mutable std::vector<int> dist_;
  mutable std::vector<int> prev_;
  bool Relax(const Parameters&) const;

 public:
  Graph(const size_t& count_vertex, const size_t& count_edges);
  const std::vector<int>& BellmanFord(const int&) const;
};

Graph::Graph(const size_t& count_vertex, const size_t& count_edges)
    : count_vertex_(count_vertex), count_edges_(count_edges) {
  int from = 0;
  int to = 0;
  int weight = 0;
  graph_.reserve(count_edges_ + 1);
  for (size_t i = 0; i < count_edges_; ++i) {
    std::cin >> from >> to >> weight;
    graph_.emplace_back(weight, from, to);
  }
}

bool Graph::Relax(const Parameters& edge) const {
  const int inf = INT32_MAX;
  if ((inf != dist_[edge.from]) && (dist_[edge.to] > dist_[edge.from] + edge.weight)) {
    prev_[edge.to] = edge.from;
    dist_[edge.to] = dist_[edge.from] + edge.weight;
    return true;
  }
  return false;
}

const std::vector<int>& Graph::BellmanFord(const int& base_vertex) const {
  const int inf = INT32_MAX;
  const int none = 0;
  dist_.resize(count_vertex_ + 1, inf);
  prev_.resize(count_vertex_ + 1, none);
  dist_[base_vertex] = 0;
  for (size_t i = 0; i < count_vertex_; ++i) {
    for (auto it : graph_) {
      Relax(it);
    }
  }
  return dist_;
}

int main() {
  size_t count_vertex = 0;
  size_t count_edges = 0;
  std::cin >> count_vertex >> count_edges;
  Graph graph(count_vertex, count_edges);
  auto dist = graph.BellmanFord(1);
  const int no_way = 30000;
  for (size_t i = 1; i < count_vertex + 1; ++i) {
    if (dist[i] != INT32_MAX) {
      std::cout << dist[i] << ' ';
    } else {
      std::cout << no_way << ' ';
    }
  }
  return 0;
}
