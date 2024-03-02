#include <iostream>
#include <vector>

class DisjointSetUnion {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  size_t count_sets_;

 public:
  void MakeSet(const size_t&);
  int FindSet(const int&);
  void Union(const int&, const int&);
  const size_t& CountSets() const;
};

void DisjointSetUnion::MakeSet(const size_t& count_sets) {
  count_sets_ = count_sets;
  parent_.resize(count_sets_);
  rank_.resize(count_sets_, 1);
  for (size_t i = 0; i < count_sets_; ++i) {
    parent_[i] = static_cast<int>(i);
  }
}

int DisjointSetUnion::FindSet(const int& element) {
  if (element == parent_[element]) {
    return element;
  }
  return parent_[element] = FindSet(parent_[element]);
}

void DisjointSetUnion::Union(const int& element1, const int& element2) {
  int root1 = FindSet(element1);
  int root2 = FindSet(element2);
  if (root1 != root2) {
    --count_sets_;
    if (rank_[root1] < rank_[root2]) {
      parent_[root1] = root2;
    } else if (rank_[root2] < rank_[root1]) {
      parent_[root2] = root1;
    } else {
      parent_[root1] = root2;
      rank_[root2] += 1;
    }
  }
}

const size_t& DisjointSetUnion::CountSets() const {
  return count_sets_;
}

int MinCountIslands(const size_t& count_islands, const size_t& count_bridges) {
  DisjointSetUnion islands;
  int min_bridges = 0;
  islands.MakeSet(count_islands);
  int vertex1 = 0;
  int vertex2 = 0;
  for (size_t i = 0; i < count_bridges; ++i) {
    ++min_bridges;
    std::cin >> vertex1 >> vertex2;
    islands.Union(vertex1, vertex2);
    if (islands.CountSets() == 1) {
      return min_bridges;
    }
  }

  return -1;
}

int main() {
  size_t count_islands = 0;
  size_t count_bridges = 0;
  std::cin >> count_islands >> count_bridges;
  std::cout << MinCountIslands(count_islands, count_bridges);
  return 0;
}
