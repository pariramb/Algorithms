#include <iostream>
#include <vector>
#include <cmath>
#include <string>

struct Node {
  size_t c_l;
  size_t c_r;
  size_t max_len;
  Node() : c_l(0), c_r(0), max_len(0) {
  }
};

template <typename T, T(Operation)(const T&, const T&)>
class SegmentTree {
  size_t size_segment_;
  size_t new_size_segment_;
  std::vector<T> tree_;
  size_t PossibleNewSize();

 public:
  explicit SegmentTree(std::string&);
  size_t Parent(const size_t&) const;
  size_t RightChild(const size_t&) const;
  size_t LeftChild(const size_t&) const;
  T Query(const size_t&, const size_t&) const;
};

template <typename T, T(Operation)(const T&, const T&)>
size_t SegmentTree<T, Operation>::PossibleNewSize() {
  auto lg_new_size = static_cast<size_t>(std::log2(size_segment_));
  size_t possible_size = 1;
  for (size_t i = 0; i < lg_new_size; ++i) {
    possible_size *= 2;
  }
  return possible_size;
}

template <typename T, T(Operation)(const T&, const T&)>
SegmentTree<T, Operation>::SegmentTree(std::string& str) : size_segment_(str.size()) {
  auto possible_size = PossibleNewSize();
  if (size_segment_ != possible_size) {
    new_size_segment_ = possible_size * 2;
  } else {
    new_size_segment_ = size_segment_;
  }
  tree_.resize(2 * new_size_segment_ - 1);
  for (size_t i = 0; i < size_segment_; ++i) {
    if (str[i] == '(') {
      tree_[i + new_size_segment_ - 1].c_l = 1;
    }
    if (str[i] == ')') {
      tree_[i + new_size_segment_ - 1].c_r = 1;
    }
  }
  for (size_t i = size_segment_; i < new_size_segment_; ++i) {
    tree_[i + new_size_segment_ - 1] = Node();
  }
  for (int64_t i = static_cast<int64_t>(new_size_segment_) - 2; i >= 0; --i) {
    tree_[i] = Operation(tree_[LeftChild(static_cast<size_t>(i))], tree_[RightChild(static_cast<size_t>(i))]);
  }
}

template <typename T, T(Operation)(const T&, const T&)>
size_t SegmentTree<T, Operation>::Parent(const size_t& child) const {
  return (child ? (child - 1) / 2 : 0);
}

template <typename T, T(Operation)(const T&, const T&)>
size_t SegmentTree<T, Operation>::RightChild(const size_t& parent) const {
  return (parent < (new_size_segment_ - 1) ? (2 * parent + 2) : 0);
}

template <typename T, T(Operation)(const T&, const T&)>
size_t SegmentTree<T, Operation>::LeftChild(const size_t& parent) const {
  return (parent < (new_size_segment_ - 1) ? (2 * parent + 1) : 0);
}

template <typename T, T(Operation)(const T&, const T&)>
T SegmentTree<T, Operation>::Query(const size_t& left, const size_t& right) const {
  auto left_temp = left + new_size_segment_ - 1;
  auto right_temp = right + new_size_segment_ - 1;
  T left_result = Node();
  T right_result = Node();
  if (left_temp == right_temp) {
    return tree_[left_temp];
  }
  while (left_temp < right_temp) {
    if (left_temp == RightChild(Parent(left_temp))) {
      left_result = Operation(left_result, tree_[left_temp]);
    }
    if (right_temp == LeftChild(Parent(right_temp))) {
      right_result = Operation(tree_[right_temp], right_result);
    }
    left_temp = Parent(left_temp + 1);
    right_temp = Parent(right_temp - 1);
  }
  if (left_temp == right_temp) {
    left_result = Operation(left_result, tree_[left_temp]);
  }
  return Operation(left_result, right_result);
}

Node Operation(const Node& node1, const Node& node2) {
  Node node;
  node.max_len = node1.max_len + node2.max_len + (std::min(node1.c_l - node1.max_len, node2.c_r - node2.max_len));
  node.c_r = node1.c_r + node2.c_r;
  node.c_l = node1.c_l + node2.c_l;
  return node;
}

void Requests(const SegmentTree<Node, Operation>& seq) {
  size_t left = 0;
  size_t right = 0;
  size_t count_requests = 0;
  std::cin >> count_requests;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> left >> right;
    std::cout << seq.Query(left - 1, right - 1).max_len * 2 << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  SegmentTree<Node, Operation> seq(str);
  Requests(seq);
  return 0;
}
