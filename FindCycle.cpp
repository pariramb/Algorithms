#include <iostream>
#include <vector>

enum Color { WHITE, GRAY, BLACK };

bool FindCycleDFS(const std::vector<std::vector<int>>& graph, std::vector<Color>& color_graph, const size_t node) {
  color_graph[node] = GRAY;
  for (size_t i = 0, size_neighbors = graph[node].size(); i < size_neighbors; ++i) {
    if (color_graph[graph[node][i]] == GRAY) {
      return true;
    }
    if (color_graph[graph[node][i]] == WHITE) {
      if (FindCycleDFS(graph, color_graph, graph[node][i])) {
        return true;
      }
    }
  }
  color_graph[node] = BLACK;
  return false;
}

bool FindCycle(const std::vector<std::vector<int>>& graph) {
  std::vector<Color> color_vertex(graph.size());
  for (size_t i = 1; i < graph.size(); ++i) {
    if (color_vertex[i] == WHITE) {
      if (FindCycleDFS(graph, color_vertex, i)) {
        return true;
      }
    }
  }
  return false;
}

void MakeGraph(std::vector<std::vector<int>>& graph, const size_t count_node) {
  char color;
  graph.resize(count_node + 1);
  for (size_t i = 1; i < count_node + 1; ++i) {
    for (size_t j = i + 1; j < count_node + 1; ++j) {
      std::cin >> color;
      if (color == 'R') {
        graph[i].emplace_back(j);
      } else {
        graph[j].emplace_back(i);
      }
    }
  }
}

int main() {
  size_t count_node;
  std::cin >> count_node;
  std::vector<std::vector<int>> graph;
  MakeGraph(graph, count_node);
  if (FindCycle(graph)) {
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
  return 0;
}
