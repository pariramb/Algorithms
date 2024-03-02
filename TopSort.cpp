#include <deque>
#include <iostream>
#include <vector>

enum Color { WHITE, GRAY, BLACK };

void MakeGraph(std::vector<std::vector<int>>& graph, const size_t count_node, const size_t count_edge) {
  int from;
  int to;
  graph.resize(count_node + 1);
  for (size_t i = 0; i < count_edge; ++i) {
    std::cin >> from;
    std::cin >> to;
    graph[from].emplace_back(to);
  }
}

void Result(const std::vector<int> sorted_graph) {
  for (auto it = sorted_graph.rbegin(); it != sorted_graph.rend(); ++it) {
    std::cout << *it << ' ';
  }
}

bool TopSordDfs(const std::vector<std::vector<int>>& graph, std::vector<Color>& color_graph,
                std::vector<int>& sorted_graph, const size_t node) {
  color_graph[node] = GRAY;
  for (size_t i = 0, size_neighbors = graph[node].size(); i < size_neighbors; ++i) {
    if ((color_graph[graph[node][i]] == GRAY)) {
      return false;
    }
    if (color_graph[graph[node][i]] == WHITE) {
      if (!TopSordDfs(graph, color_graph, sorted_graph, graph[node][i])) {
        return false;
      }
    }
  }
  color_graph[node] = BLACK;
  sorted_graph.emplace_back(node);
  return true;
}

void TopSort(const std::vector<std::vector<int>>& graph) {
  std::vector<Color> color_vertex(graph.size());
  std::vector<int> sorted_graph;
  sorted_graph.reserve(graph.size());
  for (size_t i = 1; i < graph.size(); ++i) {
    if (color_vertex[i] == WHITE) {
      if (!TopSordDfs(graph, color_vertex, sorted_graph, i)) {
        std::cout << -1;
        break;
      }
    }
    if (i == graph.size() - 1) {
      Result(sorted_graph);
    }
  }
}

int main() {
  size_t count_node;
  size_t count_edge;
  std::cin >> count_node;
  std::cin >> count_edge;
  std::vector<std::vector<int>> graph;
  MakeGraph(graph, count_node, count_edge);
  TopSort(graph);
  return 0;
}
