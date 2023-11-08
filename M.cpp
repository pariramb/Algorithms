#include <iostream>
#include <vector>

class PrefixSum {
  size_t size_;
  std::vector<uint32_t> diff_array_;
  std::vector<uint32_t> prefix_sum_;
  uint32_t Query(const uint32_t&) const;

 public:
  PrefixSum();
  void MakePrefix();
  uint32_t Query(const uint32_t&, const uint32_t&) const;
  void Update(const uint32_t&, const uint32_t&, const uint32_t&);
};

void PrefixSum::MakePrefix() {
  uint32_t value = 0;
  for (uint32_t i = 1; i < size_ + 1; ++i) {
    value += diff_array_[i];
    prefix_sum_[i] = prefix_sum_[i - 1] + value;
  }
}

PrefixSum::PrefixSum() {
  size_ = 1 << 24;
  prefix_sum_.resize(size_ + 1, 0);
  diff_array_.resize(size_ + 1, 0);
}

uint32_t PrefixSum::Query(const uint32_t& ind) const {
  return prefix_sum_[ind];
}

uint32_t PrefixSum::Query(const uint32_t& left, const uint32_t& right) const {
  return Query(right) - Query(left - 1);
}

void PrefixSum::Update(const uint32_t& left, const uint32_t& right, const uint32_t& new_value) {
  diff_array_[left] += new_value;
  diff_array_[right + 1] += -new_value;
}

uint32_t NextRand(const uint32_t& val1, const uint32_t& val2, uint32_t& cur) {
  cur = cur * val1 + val2;
  return cur >> 8;
}

void GetSegment(const uint32_t& val1, const uint32_t& val2, uint32_t& cur, uint32_t& left, uint32_t& right) {
  left = NextRand(val1, val2, cur);
  right = NextRand(val1, val2, cur);
  if (left > right) {
    std::swap(left, right);
  }
}

void Requests() {
  PrefixSum awards;
  uint32_t count_stages = 0;
  uint32_t count_queries = 0;
  uint32_t val1 = 0;
  uint32_t val2 = 0;
  uint32_t add = 0;
  uint32_t left = 0;
  uint32_t right = 0;
  uint32_t cur = 0;
  uint32_t rez = 0;
  std::cin >> count_stages >> count_queries;
  std::cin >> val1 >> val2;
  for (uint32_t i = 0; i < count_stages; ++i) {
    add = NextRand(val1, val2, cur);
    GetSegment(val1, val2, cur, left, right);
    awards.Update(left + 1, right + 1, add);
  }
  awards.MakePrefix();
  for (uint32_t i = 0; i < count_queries; ++i) {
    GetSegment(val1, val2, cur, left, right);
    rez += awards.Query(left + 1, right + 1);
  }
  std::cout << rez;
}

int main() {
  Requests();
  return 0;
}
