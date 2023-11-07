#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
  size_t size_;
  std::vector<std::vector<std::vector<T>>> partial_sum_;
  T Query(const size_t&, const size_t&, const size_t&) const;

 public:
  BinaryIndexedTree();
  T Query(const size_t&, const size_t&, const size_t&, const size_t&, const size_t&, const size_t&) const;
  void Update(const size_t&, const size_t&, const size_t&, const T&);
};

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree() {
  std::cin >> size_;
  partial_sum_.resize(size_ + 1, std::vector<std::vector<T>>(size_ + 1, std::vector<T>(size_ + 1, 0)));
}

template <typename T>
T BinaryIndexedTree<T>::Query(const size_t& x, const size_t& y, const size_t& z) const {
  T sum = 0;
  for (int i = static_cast<int>(x); i > 0; i = (i & (i + 1)) - 1) {
    for (int j = static_cast<int>(y); j > 0; j = (j & (j + 1)) - 1) {
      for (int k = static_cast<int>(z); k > 0; k = (k & (k + 1)) - 1) {
        sum += partial_sum_[i][j][k];
      }
    }
  }
  return sum;
}

template <typename T>
T BinaryIndexedTree<T>::Query(const size_t& x1, const size_t& y1, const size_t& z1, const size_t& x2, const size_t& y2,
                              const size_t& z2) const {
  return Query(x2, y2, z2) - Query(x2, y1 - 1, z2) - Query(x1 - 1, y2, z2) + Query(x1 - 1, y1 - 1, z2) -
         Query(x2, y2, z1 - 1) + Query(x1 - 1, y2, z1 - 1) + Query(x2, y1 - 1, z1 - 1) - Query(x1 - 1, y1 - 1, z1 - 1);
}

template <typename T>
void BinaryIndexedTree<T>::Update(const size_t& x, const size_t& y, const size_t& z, const T& difference) {
  for (size_t i = x; i < size_ + 1; i = i | (i + 1)) {
    for (size_t j = y; j < size_ + 1; j = j | (j + 1)) {
      for (size_t k = z; k < size_ + 1; k = k | (k + 1)) {
        partial_sum_[i][j][k] += difference;
      }
    }
  }
}

void Requests(BinaryIndexedTree<int>& space_fleets) {
  int type = 0;
  size_t x1 = 0;
  size_t y1 = 0;
  size_t z1 = 0;
  size_t x2 = 0;
  size_t y2 = 0;
  size_t z2 = 0;
  int difference = 0;
  std::cin >> type;
  while (type != 3) {
    if (type == 1) {
      std::cin >> x1 >> y1 >> z1 >> difference;
      space_fleets.Update(x1 + 1, y1 + 1, z1 + 1, difference);
    }
    if (type == 2) {
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << space_fleets.Query(x1 + 1, y1 + 1, z1 + 1, x2 + 1, y2 + 1, z2 + 1) << '\n';
    }
    std::cin >> type;
  }
}

int main() {
  BinaryIndexedTree<int> space_fleets;
  Requests(space_fleets);
  return 0;
}
