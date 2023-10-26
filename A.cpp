#include <iostream>
#include <vector>

template <typename T>
class RSQ {
  struct MaxSumSegment {
    size_t left;
    size_t right;
  };

  size_t size_;
  std::vector<T> segment_;
  std::vector<T> prefix_sum_;

 public:
  RSQ();
  T Sum(const size_t&, const size_t&) const;
};

template <typename T>
RSQ<T>::RSQ() {
  std::cin >> size_;
  if (size_) {
    segment_.resize(size_ + 1);
    prefix_sum_.resize(size_ + 1);
    segment_[0] = prefix_sum_[0] =  0;
    for (size_t i = 1; i < size_ + 1; ++i) {
      std::cin >> segment_[i];
      prefix_sum_[i] = prefix_sum_[i - 1] + segment_[i];
    }
  }
}

template <typename T>
T RSQ<T>::Sum(const size_t& left, const size_t& right) const {
  return prefix_sum_[right] - prefix_sum_[left - 1];
}

void Requests(const RSQ<size_t>& sculptures) {
  size_t count;
  std::cin >> count;
  size_t left;
  size_t right;
  for (size_t i = 0; i < count; ++i) {
    std::cin >> left >> right;
    std::cout << sculptures.Sum(left, right) << " ";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  RSQ<size_t> sculptures;
  Requests(sculptures);
}
