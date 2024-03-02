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
  enum Color { WHITE, GRAY, BLACK };
  std::vector<std::vector<Parameters>> graph_;
  size_t count_vertex_;
  size_t count_edges_;
  std::vector<Color> color_vertex_;
  std::vector<Parameters*> path_;
  int64_t max_flow_;
  int64_t possible_flow_;
  const int64_t initial_value_ = 10e6;
  void RemakeGraph();
  bool FindAndChangeAntiEdge(const size_t&, const size_t&);

 public:
  Graph(const size_t&, const size_t&);
  bool DFS(const size_t&, const size_t&);
  bool DFSVisit(const size_t&, const size_t&, int64_t&);
  int64_t FordFulkerson(const size_t&, const size_t&);
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

void Graph::RemakeGraph() {
  for (auto& edge : path_) {
    if ((graph_[edge->neighbour].empty()) || (!FindAndChangeAntiEdge(edge->neighbour, edge->vertex))) {
      graph_[edge->neighbour].emplace_back(possible_flow_, edge->neighbour, edge->vertex);
    }
    edge->capacity -= possible_flow_;
  }
}

int64_t Graph::FordFulkerson(const size_t& source, const size_t& drain) {
  max_flow_ = 0;
  while (DFS(source, drain)) {
    max_flow_ += possible_flow_;
    RemakeGraph();
    color_vertex_.clear();
    path_.clear();
  }
  return max_flow_;
}

bool Graph::DFSVisit(const size_t& node, const size_t& to, int64_t& possible_flow) {
  color_vertex_[node] = GRAY;
  for (auto& neighbour : graph_[node]) {
    if (color_vertex_[neighbour.neighbour] == WHITE) {
      if (neighbour.capacity == 0) {
        continue;
      }
      if (possible_flow > neighbour.capacity) {
        possible_flow = neighbour.capacity;
      }
      if (neighbour.neighbour == to) {
        path_.emplace_back(&neighbour);
        return true;
      }
      if (DFSVisit(neighbour.neighbour, to, possible_flow)) {
        path_.emplace_back(&neighbour);
        return true;
      }
    }
  }
  color_vertex_[node] = BLACK;
  return false;
}

bool Graph::DFS(const size_t& from, const size_t& to) {
  color_vertex_.resize(graph_.size(), WHITE);
  possible_flow_ = initial_value_;
  return DFSVisit(from, to, possible_flow_);
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
  std::cout << graph.FordFulkerson(1, count_node);
  return 0;
}
