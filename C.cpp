////// SparseTable
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class RMQ {
  size_t size_;
  std::vector<std::vector<T>> sparse_table_;
  std::vector<size_t> power_of_two_;

 public:
  explicit RMQ(size_t);
  T Min(const size_t&, size_t) const;
};

template <typename T>
RMQ<T>::RMQ(size_t size) {
  if (size) {
    size_ = size;
    sparse_table_.resize(size_ + 1);
    for (size_t i = 1; i < size_ + 1; ++i) {
      sparse_table_[i].resize(static_cast<size_t>(std::log2(size_ - (i - 1))) + 1);
    }
    auto max_pow = static_cast<size_t>(log2(size_));
    power_of_two_.resize(max_pow + 1, 1);
    for (size_t i = 1; i < max_pow + 1; ++i) {
      power_of_two_[i] = power_of_two_[i - 1] * 2;
    }
    // build table
    for (size_t i = 1; i < size_ + 1; ++i) {
      std::cin >> sparse_table_[i][0];
    }
    for (size_t j = 1, size_of_j_line = 0; j < max_pow + 1; ++j) {
      size_of_j_line = size_ - power_of_two_[j] + 1;
      for (size_t i = 1; i < size_of_j_line + 1; ++i) {
        auto a = i + power_of_two_[j - 1];
        sparse_table_[i][j] = std::min(sparse_table_[i][j - 1], sparse_table_[a][j - 1]);
      }
    }
  }
}

template <typename T>
T RMQ<T>::Min(const size_t& left, size_t right) const {
  auto max_pow = static_cast<size_t>(std::log2(right - left + 1));
  return std::min(sparse_table_[left][max_pow], sparse_table_[right - power_of_two_[max_pow] + 1][max_pow]);
}

void Request(const RMQ<size_t>& releases, const size_t& count_requests) {
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> left >> right;
    std::cout << releases.Min(left, right) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t count_kikoriki = 0;
  size_t count_requests = 0;
  std::cin >> count_kikoriki >> count_requests;
  RMQ<size_t> releases(count_kikoriki);
  Request(releases, count_requests);
  return 0;
}
