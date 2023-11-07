#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
  size_t size_;
  std::vector<T> segment_;
  std::vector<T> prefix_sum_;
  std::vector<T> partial_sum_;
  size_t LowIndSegment(const size_t&);
  T Query(const size_t&) const;

 public:
  BinaryIndexedTree();
  T Query(const size_t&, const size_t&) const;
  void Update(const size_t&, const T&);
};

template <typename T>
size_t BinaryIndexedTree<T>::LowIndSegment(const size_t& ind) {
  return (ind & (ind + 1) ? ind & (ind + 1) : 1);
}

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree() {
  std::cin >> size_;
  prefix_sum_.resize(size_ + 1, 0);
  segment_.resize(size_ + 1, 0);
  for (size_t i = 1; i < size_ + 1; ++i) {
    std::cin >> segment_[i];
    prefix_sum_[i] = prefix_sum_[i - 1] + segment_[i];
  }
  partial_sum_.resize(size_ + 1, 0);
  for (size_t i = 1; i < size_ + 1; ++i) {
    partial_sum_[i] = prefix_sum_[i] - prefix_sum_[LowIndSegment(i) - 1];
  }
}

template <typename T>
T BinaryIndexedTree<T>::Query(const size_t& right) const {
  T sum = 0;
  for (int i = static_cast<int>(right); i > 0; i = (i & (i + 1)) - 1) {
    sum += partial_sum_[i];
  }
  return sum;
}

template <typename T>
T BinaryIndexedTree<T>::Query(const size_t& left, const size_t& right) const {
  return Query(right) - Query(left - 1);
}

template <typename T>
void BinaryIndexedTree<T>::Update(const size_t& ind, const T& new_value) {
  for (size_t i = ind; i < size_ + 1; i = i | (i + 1)) {
    partial_sum_[i] += (new_value - segment_[ind]);
  }
  segment_[ind] = new_value;
}

void Requests(BinaryIndexedTree<int64_t>& exhibits) {
  size_t count_requests = 0;
  std::cin >> count_requests;
  char type = 0;
  size_t ind1 = 0;
  size_t ind2 = 0;
  int64_t value = 0;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> type;
    if (type == 's') {
      std::cin >> ind1 >> ind2;
      std::cout << exhibits.Query(ind1, ind2) << ' ';
    }
    if (type == 'u') {
      std::cin >> ind1 >> value;
      exhibits.Update(ind1, value);
    }
  }
}

int main() {
  BinaryIndexedTree<int64_t> exhibits;
  Requests(exhibits);
  return 0;
}
