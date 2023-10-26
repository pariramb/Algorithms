////// SparseTable многомерная
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class RMQ {
  size_t row_;
  size_t column_;
  std::vector<std::vector<std::vector<std::vector<T>>>> sparse_table_;
  std::vector<size_t> power_of_two_;

 public:
  RMQ(const size_t&, const size_t&);
  T Min(const size_t&, const size_t&, const size_t&, const size_t&) const;
};

template <typename T>
RMQ<T>::RMQ(const size_t& row, const size_t& column) : row_(row), column_(column) {
  if ((row) || (column)) {
    sparse_table_.resize(row_ + 1);
    for (size_t i = 1; i < row_ + 1; ++i) {
      sparse_table_[i].resize(column_ + 1);
      size_t count = (static_cast<size_t>(std::log2(row_ - (i - 1))) + 1);
      for (size_t j = 1; j < column_ + 1; ++j) {
        sparse_table_[i][j].resize(count);
        size_t count1 = (static_cast<size_t>(std::log2(column_ - (j - 1))) + 1);
        for (size_t k = 0; k < count; ++k) {
          sparse_table_[i][j][k].resize(count1);
        }
      }
    }
    auto lgrow = static_cast<size_t>(log2(static_cast<double>(row_)));
    auto lgcol = static_cast<size_t>(log2(static_cast<double>(column_)));
    auto max_pow = std::max(lgcol, lgrow);
    power_of_two_.resize(max_pow + 1, 1);
    for (size_t i = 1; i < max_pow + 1; ++i) {
      power_of_two_[i] = power_of_two_[i - 1] * 2;
    }
    // build table
    for (size_t i = 1; i < row_ + 1; ++i) {
      for (size_t j = 1; j < column_ + 1; ++j) {
        std::cin >> sparse_table_[i][j][0][0];
      }
    }
    for (size_t i = 1; i < row_ + 1; ++i) {
      for (size_t k1 = 1, size_of_j_line = 0; k1 < lgcol + 1; ++k1) {
        size_of_j_line = column_ - power_of_two_[k1] + 1;
        for (size_t j = 1; j < size_of_j_line + 1; ++j) {
          auto ind = j + power_of_two_[k1 - 1];
          sparse_table_[i][j][0][k1] = std::min(sparse_table_[i][j][0][k1 - 1], sparse_table_[i][ind][0][k1 - 1]);
        }
      }
    }
    for (size_t k1 = 1, size_of_i_line = 0; k1 < lgrow + 1; ++k1) {
      size_of_i_line = row_ - power_of_two_[k1] + 1;
      for (size_t i = 1; i < size_of_i_line + 1; ++i) {
        for (size_t k2 = 0, size_of_j_line = 0; k2 < lgcol + 1; ++k2) {
          size_of_j_line = column_ - power_of_two_[k2] + 1;
          for (size_t j = 1; j < size_of_j_line + 1; ++j) {
            sparse_table_[i][j][k1][k2] =
                std::min(sparse_table_[i][j][k1 - 1][k2], sparse_table_[i + power_of_two_[k1 - 1]][j][k1 - 1][k2]);
          }
        }
      }
    }
  }
}
template <typename T>
T RMQ<T>::Min(const size_t& x1, const size_t& x2, const size_t& y1, const size_t& y2) const {
  auto max_pow_x = static_cast<size_t>(std::log2(x2 - x1 + 1));
  auto max_pow_y = static_cast<size_t>(std::log2(y2 - y1 + 1));
  auto ind2 = power_of_two_[max_pow_y] - 1;
  auto ind1 = power_of_two_[max_pow_x] - 1;
  T ans1 = std::min(sparse_table_[x1][y1][max_pow_x][max_pow_y], sparse_table_[x2 - ind1][y1][max_pow_x][max_pow_y]);
  T ans2 = std::min(sparse_table_[x1][y2 - ind2][max_pow_x][max_pow_y],
                    sparse_table_[x2 - ind1][y2 - ind2][max_pow_x][max_pow_y]);
  return std::min(ans1, ans2);
}

void Request(const RMQ<int>& releases, const size_t& count_requests) {
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << releases.Min(x1, x2, y1, y2) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t row = 0;
  size_t column = 0;
  std::cin >> row >> column;
  RMQ<int> releases(row, column);
  size_t count_requests = 0;
  std::cin >> count_requests;
  Request(releases, count_requests);
  return 0;
}
