#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  size_t count_vertex_;

 public:
  explicit Graph(const size_t&);
  const std::vector<std::vector<int>>& FloydWarshall();
};

const std::vector<std::vector<int>>& Graph::FloydWarshall() {
  for (size_t k = 0; k < count_vertex_; ++k) {
    for (size_t i = 0; i < count_vertex_; ++i) {
      for (size_t j = 0; j < count_vertex_; ++j) {
        graph_[i][j] = std::min(graph_[i][j], graph_[i][k] + graph_[k][j]);
      }
    }
  }
  return graph_;
}

Graph::Graph(const size_t& count_vertex) : count_vertex_(count_vertex) {
  std::vector<int> temp(count_vertex_ + 1);
  graph_.resize(count_vertex_ + 1, temp);
  for (size_t i = 0; i < count_vertex_; ++i) {
    for (size_t j = 0; j < count_vertex_; ++j) {
      std::cin >> graph_[i][j];
    }
  }
}

void Result() {
  size_t count_vertex = 0;
  std::cin >> count_vertex;
  Graph graph(count_vertex);
  auto result = graph.FloydWarshall();
  for (size_t i = 0; i < count_vertex; ++i) {
    for (size_t j = 0; j < count_vertex; ++j) {
      std::cout << result[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  Result();
  return 0;
}