#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  struct Parameters {
    size_t weight;
    size_t vertex;
    Parameters(size_t weight, size_t vertex) : weight(weight), vertex(vertex) {
    }
  };
  std::vector<std::vector<Parameters>> graph_;
  size_t count_vertex_;
  size_t count_edges_;
  std::vector<size_t> dist_;

 public:
  Graph(size_t count_vertex, size_t count_edges);
  const std::vector<size_t>& Dijkstra(size_t);
  friend struct Compare;
};

struct Compare {
  bool operator()(const Graph::Parameters& first, const Graph::Parameters& second) {
    return first.weight > second.weight;
  }
};

const std::vector<size_t>& Graph::Dijkstra(size_t vertex) {
  const size_t inf = 2009000999;
  const size_t none = count_vertex_;
  std::vector<char> is_used(count_vertex_, 0);
  dist_.resize(count_vertex_, inf);
  dist_[vertex] = 0;
  std::vector<size_t> prev(count_vertex_, none);
  std::priority_queue<Parameters, std::vector<Parameters>, Compare> possible_candidates;
  possible_candidates.emplace(0, vertex);
  while (!possible_candidates.empty()) {
    while (is_used[possible_candidates.top().vertex]) {
      possible_candidates.pop();
      if (possible_candidates.empty()) {
        return dist_;
      }
    }
    auto vertex_min = possible_candidates.top();
    possible_candidates.pop();
    is_used[vertex_min.vertex] = 1;
    for (auto it : graph_[vertex_min.vertex]) {
      if ((!is_used[it.vertex]) && (it.weight + dist_[vertex_min.vertex] < dist_[it.vertex])) {
        prev[it.vertex] = vertex_min.vertex;
        dist_[it.vertex] = it.weight + dist_[vertex_min.vertex];
        possible_candidates.emplace(dist_[it.vertex], it.vertex);
      }
    } 
  }
  return dist_;
}

Graph::Graph(size_t count_vertex, size_t count_edges) : count_vertex_(count_vertex), count_edges_(count_edges) {
  size_t vertex1 = 0;
  size_t vertex2 = 0;
  size_t weight = 0;
  graph_.resize(count_vertex_);
  for (size_t i = 0; i < count_edges_; ++i) {
    std::cin >> vertex1 >> vertex2 >> weight;
    graph_[vertex1].emplace_back(weight, vertex2);
    graph_[vertex2].emplace_back(weight, vertex1);
  }
}

void Result() {
  size_t count_iterations = 0;
  std::cin >> count_iterations;
  size_t count_vertex = 0;
  size_t count_bridges = 0;
  size_t base_vertex = 0;
  for (size_t i = 0; i < count_iterations; ++i) {
    std::cin >> count_vertex >> count_bridges;
    Graph graph(count_vertex, count_bridges);
    std::cin >> base_vertex;
    auto dist = graph.Dijkstra(base_vertex);
    for (size_t i = 0; i < count_vertex; ++i) {
      std::cout << dist[i] << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Result();
  return 0;
}
