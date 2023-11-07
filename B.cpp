#include <iostream>
#include <vector>

template <typename T>
class RSQ {
  struct MaxSumSegment {
    size_t left;
    size_t right;
    explicit MaxSumSegment(const size_t& left1 = 0, const size_t& right1 = 0) : left(left1), right(right1) {
    }
  };

  size_t size_;
  std::vector<T> segment_;
  std::vector<T> prefix_sum_;

 public:
  RSQ();
  T Sum(const size_t&, const size_t&) const;
  std::pair<MaxSumSegment, T> FindMaxSumSegment() const;
};

template <typename T>
RSQ<T>::RSQ() {
  std::cin >> size_;
  if (size_) {
    segment_.resize(size_ + 1);
    prefix_sum_.resize(size_ + 1);
    segment_[0] = prefix_sum_[0] = 0;
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

template <typename T>
std::pair<typename RSQ<T>::MaxSumSegment, T> RSQ<T>::FindMaxSumSegment() const {
  if (size_) {
    T min_prefix = std::min(prefix_sum_[0], prefix_sum_[1]);
    size_t ind_min_prefix = (prefix_sum_[0] == min_prefix ? 0 : 1);
    MaxSumSegment segment(1, 1);
    T sum = prefix_sum_[1];
    for (size_t i = 2; i < size_ + 1; ++i) {
      if (prefix_sum_[i] - min_prefix > sum) {
        sum = prefix_sum_[i] - min_prefix;
        segment = MaxSumSegment(ind_min_prefix + 1, i);
      }
      if (min_prefix > prefix_sum_[i]) {
        min_prefix = prefix_sum_[i];
        ind_min_prefix = i;
      }
    }
    return std::make_pair<MaxSumSegment, T>(std::move(segment), std::move(sum));
  }
  return std::make_pair<MaxSumSegment, T>(MaxSumSegment(), 0);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  RSQ<int> kikoriki;
  auto group = kikoriki.FindMaxSumSegment();
  std::cout << group.first.left << ' ' << group.first.right << ' ' << group.second;
}
