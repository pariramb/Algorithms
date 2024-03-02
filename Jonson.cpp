#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  struct Parameters {
    int64_t weight;
    size_t vertex;
    Parameters(int64_t weight, size_t vertex) : weight(weight), vertex(vertex) {
    }
  };
  std::vector<std::vector<Parameters>> graph_;
  size_t count_vertex_;
  size_t count_edges_;
  std::vector<int64_t> dist_;
  std::vector<size_t> prev_;
  bool Relax(const size_t&, const Parameters&);
  std::vector<int64_t> changed_weight_;

 public:
  Graph(size_t count_vertex, size_t count_edges);
  int64_t Dijkstra(const size_t&);
  const std::vector<int64_t>& BellmanFord(const size_t&);
  int64_t Jonson();
  friend struct Compare;
};

struct Compare {
  bool operator()(const Graph::Parameters& first, const Graph::Parameters& second) {
    return first.weight > second.weight;
  }
};

bool Graph::Relax(const size_t& from, const Parameters& edge) {
  const int64_t inf = 20000000000000;
  if ((inf != dist_[from]) && (dist_[edge.vertex] > dist_[from] + edge.weight)) {
    prev_[edge.vertex] = from;
    dist_[edge.vertex] = dist_[from] + edge.weight;
    return true;
  }
  return false;
}

const std::vector<int64_t>& Graph::BellmanFord(const size_t& base_vertex) {
  const int64_t inf = 20000000000000;
  const size_t none = 0;
  dist_.resize(count_vertex_ + 1, inf);
  prev_.resize(count_vertex_ + 1, none);
  dist_[base_vertex] = 0;
  std::vector<char> is_used(count_vertex_ + 1, 0);
  for (size_t i = 0; i < count_vertex_ - 1; ++i) {
    for (size_t i = 0; i < count_vertex_ + 1; ++i) {
      for (auto it : graph_[i]) {
        Relax(i, it);
      }
    }
  }
  return dist_;
}

int64_t Graph::Dijkstra(const size_t& vertex) {
  const int64_t inf = 2009000999;
  const size_t none = count_vertex_;
  std::vector<char> is_used(count_vertex_ + 1, 0);
  dist_.resize(count_vertex_ + 1, inf);
  dist_[vertex] = 0;
  std::vector<size_t> prev(count_vertex_ + 1, none);
  std::priority_queue<Parameters, std::vector<Parameters>, Compare> possible_candidates;
  possible_candidates.emplace(0, vertex);
  int64_t max_dist = -inf;
  while (!possible_candidates.empty()) {
    while (is_used[possible_candidates.top().vertex]) {
      possible_candidates.pop();
      if (possible_candidates.empty()) {
        for (size_t i = 0; i < count_vertex_; ++i) {
          if ((dist_[i] != inf) && (max_dist < dist_[i] + changed_weight_[i] - changed_weight_[vertex])) {
            max_dist = dist_[i] + changed_weight_[i] - changed_weight_[vertex];
          }
        }
        dist_.clear();
        return max_dist;
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
  for (size_t i = 0; i < count_vertex_; ++i) {
    if ((dist_[i] != inf) && (max_dist < dist_[i] + changed_weight_[i] - changed_weight_[vertex])) {
      max_dist = dist_[i] + changed_weight_[i] - changed_weight_[vertex];
    }
  }
  dist_.clear();
  return max_dist;
}

int64_t Graph::Jonson() {
  changed_weight_ = BellmanFord(count_vertex_);
  dist_.clear();
  for (size_t i = 0; i < count_vertex_ + 1; ++i) {
    for (auto& it : graph_[i]) {
      auto temp = changed_weight_[i] - changed_weight_[it.vertex];
      it.weight += temp;
    }
  }
  int64_t max_dist = 0;
  for (size_t i = 0; i < count_vertex_; ++i) {
    auto max_temp = Dijkstra(i);
    if (max_dist < max_temp) {
      max_dist = max_temp;
    }
  }
  return max_dist;
}

Graph::Graph(size_t count_vertex, size_t count_edges) : count_vertex_(count_vertex), count_edges_(count_edges) {
  size_t vertex1 = 0;
  size_t vertex2 = 0;
  int64_t weight = 0;
  graph_.resize(count_vertex_ + 1);
  for (size_t i = 0; i < count_edges_; ++i) {
    std::cin >> vertex1 >> vertex2 >> weight;
    graph_[vertex1].emplace_back(weight, vertex2);
  }
  for (size_t i = 0; i < count_vertex_; ++i) {
    graph_[count_vertex_].emplace_back(0, i);
  }
}

int main() {
  size_t count_vertex = 0;
  size_t count_edges = 0;
  std::cin >> count_vertex >> count_edges;
  Graph graph(count_vertex, count_edges);
  std::cout << graph.Jonson();
  return 0;
}
