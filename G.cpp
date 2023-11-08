#include <iostream>
#include <vector>
#include <cmath>

template <typename T, T(Operation)(const T&, const T&)>
class SegmentTree {
  size_t size_segment_;
  size_t new_size_segment_;
  std::vector<T> tree_;
  size_t PossibleNewSize();

 public:
  SegmentTree();
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
SegmentTree<T, Operation>::SegmentTree() {
  std::cin >> size_segment_;
  if (size_segment_) {
    auto possible_size = PossibleNewSize();
    if (size_segment_ != possible_size) {
      new_size_segment_ = possible_size * 2;
    } else {
      new_size_segment_ = size_segment_;
    }
    tree_.resize(2 * new_size_segment_ - 1);
    for (size_t i = 0; i < size_segment_; ++i) {
      std::cin >> tree_[i + new_size_segment_ - 1];
    }
    for (size_t i = size_segment_; i < new_size_segment_; ++i) {
      tree_[i + new_size_segment_ - 1] = T();
    }
    for (int64_t i = static_cast<int64_t>(new_size_segment_) - 2; i >= 0; --i) {
      tree_[i] = Operation(tree_[LeftChild(static_cast<size_t>(i))], tree_[RightChild(static_cast<size_t>(i))]);
    }
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
  T left_result = T();
  T right_result = T();
  if (left_temp == right_temp) {
    return tree_[left_temp];
  }
  while (left_temp < right_temp) {
    if (left_temp == RightChild(Parent(left_temp))) {
      left_result = Operation(left_result, tree_[left_temp]);
    }
    left_temp = Parent(left_temp + 1);
    if (right_temp == LeftChild(Parent(right_temp))) {
      right_result = Operation(tree_[right_temp], right_result);
    }
    right_temp = Parent(right_temp - 1);
  }
  if (left_temp == right_temp) {
    left_result = Operation(left_result, tree_[left_temp]);
    // right_result = Operation(tree_[right_temp], right_result);
  }
  return Operation(left_result, right_result);
}

struct Node {
  int max;
  size_t count_max;
  explicit Node(int max = INT32_MIN, size_t count_max = 1) : max(max), count_max(count_max) {
  }
};

bool operator==(const Node& node1, const Node& node2) {
  return (node1.max == node2.max);
}

bool operator>=(const Node& node1, const Node& node2) {
  return (node1.count_max >= node2.count_max);
}

std::istream& operator>>(std::istream& is, Node& node) {
  is >> node.max;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
  os << node.max << ' ' << node.count_max;
  return os;
}

Node Min(const Node& node1, const Node& node2) {
  size_t count_max = 0;
  if (node1.max == node2.max) {
    count_max = node1.count_max + node2.count_max;
  } else {
    count_max = (node1.max > node2.max ? node1.count_max : node2.count_max);
  }
  return Node(std::max(node1.max, node2.max), count_max);
}

void Requests(const SegmentTree<Node, Min>& kikoriki) {
  size_t left = 0;
  size_t right = 0;
  size_t count_requests = 0;
  std::cin >> count_requests;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> left >> right;
    std::cout << kikoriki.Query(left - 1, right - 1) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  SegmentTree<Node, Min> kikoriki;
  Requests(kikoriki);
  return 0;
}
