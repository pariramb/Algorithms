#include <deque>
#include <iostream>
#include <vector>

class Graph {
 private:
  struct Parameters {
    size_t vertex;
    int64_t capacity;
    size_t neighbour;
    Parameters(const int64_t& capacity, const size_t& from, const size_t& to)
        : vertex(from), capacity(capacity), neighbour(to) {
    }
  };
  std::vector<std::vector<Parameters>> graph_;
  size_t count_vertex_;
  size_t count_edges_;
  std::vector<Parameters*> path_;
  std::deque<size_t> queue_;
  int64_t max_flow_;
  int64_t possible_flow_;
  const int64_t initial_value_ = 10e6;
  const int inf_ = -1;
  void RemakeGraph(const size_t&, const size_t&);
  bool FindAndChangeAntiEdge(const size_t&, const size_t&);

 public:
  Graph(const size_t&, const size_t&);
  int64_t EdmondsKarp(const size_t&, const size_t&);
  bool BFS(const size_t&, const size_t&);
};

bool Graph::FindAndChangeAntiEdge(const size_t& neighbour, const size_t& vertex) {
  for (auto& edge1 : graph_[neighbour]) {
    if (edge1.neighbour == vertex) {
      edge1.capacity += possible_flow_;
      return true;
    }
  }
  return false;
}

void Graph::RemakeGraph(const size_t& from, const size_t& to) {
  auto vertex = path_[to];
  while (vertex->neighbour != from) {
    if (possible_flow_ > vertex->capacity) {
      possible_flow_ = vertex->capacity;
    }
    vertex = path_[vertex->vertex];
  }
  vertex = path_[to];
  while (vertex->neighbour != from) {
    if ((graph_[vertex->neighbour].empty()) || (!FindAndChangeAntiEdge(vertex->neighbour, vertex->vertex))) {
      graph_[vertex->neighbour].emplace_back(possible_flow_, vertex->neighbour, vertex->vertex);
    }
    vertex->capacity -= possible_flow_;
    vertex = path_[vertex->vertex];
  }
}

int64_t Graph::EdmondsKarp(const size_t& source, const size_t& drain) {
  max_flow_ = 0;
  path_.resize(count_vertex_ + 1);
  Parameters artificial_edge = {1, 0, 1};
  path_[1] = &artificial_edge;
  while (BFS(source, drain)) {
    possible_flow_ = initial_value_;
    RemakeGraph(source, drain);
    max_flow_ += possible_flow_;
  }
  return max_flow_;
}

bool Graph::BFS(const size_t& from, const size_t& to) {
  queue_.push_front(from);
  std::vector<int64_t> dist(count_vertex_ + 1, inf_);
  dist[from] = 0;
  while (!queue_.empty()) {
    size_t top = queue_.back();
    queue_.pop_back();
    for (auto& neighbour : graph_[top]) {
      if (dist[neighbour.neighbour] == inf_) {
        if (neighbour.capacity == 0) {
          continue;
        }
        path_[neighbour.neighbour] = &neighbour;
        if (neighbour.neighbour == to) {
          queue_.clear();
          return true;
        }
        dist[neighbour.neighbour] = dist[top] + 1;
        queue_.push_front(neighbour.neighbour);
      }
    }
  }
  return false;
}

Graph::Graph(const size_t& count_vertex, const size_t& count_edges)
    : count_vertex_(count_vertex), count_edges_(count_edges) {
  size_t vertex1 = 0;
  size_t vertex2 = 0;
  int64_t capacity = 0;
  graph_.resize(count_vertex_ + 1);
  for (size_t i = 0; i < count_edges_; ++i) {
    std::cin >> vertex1 >> vertex2 >> capacity;
    graph_[vertex1].emplace_back(capacity, vertex1, vertex2);
  }
}

int main() {
  size_t count_node = 0;
  size_t count_edge = 0;
  std::cin >> count_node;
  std::cin >> count_edge;
  Graph graph(count_node, count_edge);
  std::cout << graph.EdmondsKarp(1, count_node);
  return 0;
}
