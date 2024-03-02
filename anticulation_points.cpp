#include <algorithm>
#include <iostream>
#include <vector>

enum Color { WHITE, GRAY, BLACK };

void Result(std::vector<bool>& anticulation_points) {
  size_t anticulation_points_count = 0;
  for (size_t i = 1; i < anticulation_points.size(); ++i) {
    if (anticulation_points[i]) {
      ++anticulation_points_count;
    }
  }
  std::cout << anticulation_points_count << '\n';
  for (size_t i = 1; i < anticulation_points.size(); ++i) {
    if (anticulation_points[i]) {
      std::cout << i << '\n';
    }
  }
}

void DFSVisit(const std::vector<std::vector<int>>& graph, std::vector<Color>& color_graph, const int node,
              std::vector<size_t>& time_in, std::vector<size_t>& time_up, size_t& time, bool is_root,
              std::vector<bool>& anticulation_points) {
  color_graph[node] = GRAY;
  time_in[node] = time_up[node] = ++time;
  size_t count_children = 0;
  for (size_t i = 0, size_neighbors = graph[node].size(); i < size_neighbors; ++i) {
    if ((color_graph[graph[node][i]] == GRAY) && (graph[node][i] != node)) {
      time_up[node] = std::min(time_up[node], time_in[graph[node][i]]);
    }
    if (color_graph[graph[node][i]] == WHITE) {
      ++count_children;
      DFSVisit(graph, color_graph, graph[node][i], time_in, time_up, time, false, anticulation_points);
      time_up[node] = std::min(time_up[node], time_up[graph[node][i]]);
      if ((!is_root) && (time_in[node] <= time_up[graph[node][i]])) {
        anticulation_points[node] = true;
      }
    }
  }
  if (is_root && (count_children > 1)) {
    anticulation_points[node] = true;
  }
  color_graph[node] = BLACK;
}

void DFS(const std::vector<std::vector<int>>& graph) {
  std::vector<Color> color_vertex(graph.size());
  std::vector<size_t> time_in(graph.size());
  std::vector<size_t> time_up(graph.size());
  std::vector<bool> anticulation_points(graph.size(), false);
  size_t time = 0;
  for (size_t i = 1; i < graph.size(); ++i) {
    if (color_vertex[i] == WHITE) {
      DFSVisit(graph, color_vertex, i, time_in, time_up, time, true, anticulation_points);
    }
  }
  Result(anticulation_points);
}

void MakeGraph(std::vector<std::vector<int>>& graph, const size_t count_node, const size_t count_edge) {
  int from;
  int to;
  graph.resize(count_node + 1);
  for (size_t i = 0; i < count_edge; ++i) {
    std::cin >> from;
    std::cin >> to;
    graph[from].emplace_back(to);
    graph[to].emplace_back(from);
  }
}

int main() {
  size_t count_node;
  size_t count_edge;
  std::cin >> count_node;
  std::cin >> count_edge;
  std::vector<std::vector<int>> graph;
  MakeGraph(graph, count_node, count_edge);
  DFS(graph);
  return 0;
}
