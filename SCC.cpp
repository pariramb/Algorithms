#include <iostream>
#include <vector>

enum Color { WHITE, GRAY, BLACK };

void Result(const std::vector<int>& vertex, const size_t size) {
  std::cout << size << '\n';
  for (size_t i = 1; i < vertex.size(); ++i) {
    std::cout << vertex[i] << ' ';
  }
}

void Transpose(const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& transpose_graph) {
  transpose_graph.resize(graph.size());
  for (size_t i = 1; i < graph.size(); ++i) {
    for (size_t j = 0; j < graph[i].size(); ++j) {
      transpose_graph[graph[i][j]].emplace_back(i);
    }
  }
}

bool TopSortNoCycleDfs(const std::vector<std::vector<int>>& graph, std::vector<Color>& color_graph,
                       std::vector<int>& sorted_graph, const size_t node) {
  color_graph[node] = GRAY;
  for (size_t i = 0, size_neighbors = graph[node].size(); i < size_neighbors; ++i) {  // петли циклы
    if (color_graph[graph[node][i]] == WHITE) {
      TopSortNoCycleDfs(graph, color_graph, sorted_graph, graph[node][i]);
    }
  }
  color_graph[node] = BLACK;
  sorted_graph.emplace_back(node);
  return true;
}

std::vector<int>& TopSortNoCycle(const std::vector<std::vector<int>>& graph, std::vector<int>& sorted_graph) {
  std::vector<Color> color_vertex(graph.size());
  std::vector<int> sorted_graph_temp;
  sorted_graph_temp.reserve(graph.size());
  for (size_t i = 1; i < graph.size(); ++i) {
    if (color_vertex[i] == WHITE) {
      TopSortNoCycleDfs(graph, color_vertex, sorted_graph_temp, i);
    }
  }
  sorted_graph.reserve(graph.size());
  for (auto it = sorted_graph_temp.rbegin(); it != sorted_graph_temp.rend(); ++it) {
    sorted_graph.emplace_back(*it);
  }
  return sorted_graph;
}

void DFSVisit(const std::vector<std::vector<int>>& graph, std::vector<int>& vertex, std::vector<Color>& color_graph,
              const size_t size, const size_t node) {
  color_graph[node] = GRAY;
  for (size_t i = 0, size_neighbors = graph[node].size(); i < size_neighbors; ++i) {
    if (color_graph[graph[node][i]] == WHITE) {
      vertex[graph[node][i]] = size;
      DFSVisit(graph, vertex, color_graph, size, graph[node][i]);
    }
  }
  color_graph[node] = BLACK;
}

void DFS(const std::vector<std::vector<int>>& graph, const std::vector<int>& sorted_graph) {
  std::vector<Color> color_vertex(graph.size());
  std::vector<int> vertex(graph.size());
  size_t size = 0;
  for (size_t i = 0; i < sorted_graph.size(); ++i) {
    if (color_vertex[sorted_graph[i]] == WHITE) {
      ++size;
      vertex[sorted_graph[i]] = size;
      DFSVisit(graph, vertex, color_vertex, size, sorted_graph[i]);
    }
  }
  Result(vertex, size);
}

void SCC(const std::vector<std::vector<int>>& graph) {
  std::vector<int> sorted_graph;
  sorted_graph = TopSortNoCycle(graph, sorted_graph);
  std::vector<std::vector<int>> trans_graph;
  Transpose(graph, trans_graph);
  DFS(trans_graph, sorted_graph);
}

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

int main() {
  size_t count_node;
  size_t count_edge;
  std::cin >> count_node;
  std::cin >> count_edge;
  std::vector<std::vector<int>> graph;
  MakeGraph(graph, count_node, count_edge);
  SCC(graph);
  return 0;
}
