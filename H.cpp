#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
class SegmentTree {
  struct Node {
    T value;
    T promise;
    Node() : value(DefaultOperation), promise(DefaultUpdate) {
    }
  };
  size_t size_segment_;
  size_t new_size_segment_;
  std::vector<Node> tree_;
  size_t PossibleNewSize();
  T Query(const size_t&, const size_t&, const size_t&, const size_t&, const size_t&);
  void Push(const size_t&);
  void Update(const size_t&, const size_t&, const size_t&, const size_t&, const size_t&, const T&);

 public:
  SegmentTree();
  size_t RightChild(const size_t&) const;
  size_t LeftChild(const size_t&) const;
  T Query(const size_t&, const size_t&);
  void Update(const size_t&, const size_t&, const T&);
};

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
void SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::Update(const size_t& left,
                                                                                  const size_t& right, const T& add) {
  Update(0, 0, new_size_segment_ - 1, left, right, add);
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
void SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::Update(const size_t& curr_node,
                                                                                  const size_t& left_covered,
                                                                                  const size_t& right_covered,
                                                                                  const size_t& left,
                                                                                  const size_t& right, const T& add) {
  if ((left <= left_covered) && (right_covered <= right)) {
    tree_[curr_node].promise = UpdateOp(tree_[curr_node].promise, add);
    return;
  }
  if ((right_covered < left) || (left_covered > right)) {
    return;
  }
  Push(curr_node);
  Update(LeftChild(curr_node), left_covered, (right_covered + left_covered) / 2, left, right, add);
  Update(RightChild(curr_node), (right_covered + left_covered) / 2 + 1, right_covered, left, right, add);
  tree_[curr_node].value =
      Operation(UpdateOp(tree_[LeftChild(curr_node)].value, tree_[LeftChild(curr_node)].promise),
                UpdateOp(tree_[RightChild(curr_node)].value, tree_[RightChild(curr_node)].promise));
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
void SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::Push(const size_t& node) {
  tree_[node].value = UpdateOp(tree_[node].value, tree_[node].promise);
  tree_[LeftChild(node)].promise = UpdateOp(tree_[LeftChild(node)].promise, tree_[node].promise);
  tree_[RightChild(node)].promise = UpdateOp(tree_[RightChild(node)].promise, tree_[node].promise);
  tree_[node].promise = DefaultUpdate;
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
size_t SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::PossibleNewSize() {
  auto lg_new_size = static_cast<size_t>(std::log2(size_segment_));
  size_t possible_size = 1;
  for (size_t i = 0; i < lg_new_size; ++i) {
    possible_size *= 2;
  }
  return possible_size;
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::SegmentTree() {
  std::cin >> size_segment_;
  if (size_segment_) {
    auto possible_size = PossibleNewSize();
    if (size_segment_ != possible_size) {
      new_size_segment_ = possible_size * 2;
    } else {
      new_size_segment_ = size_segment_;
    }
    tree_.resize(2 * new_size_segment_ - 1, Node());
    for (size_t i = 0; i < size_segment_; ++i) {
      std::cin >> tree_[i + new_size_segment_ - 1].value;
    }
    for (int64_t i = static_cast<int64_t>(new_size_segment_) - 2; i >= 0; --i) {
      tree_[i].value =
          Operation(tree_[LeftChild(static_cast<size_t>(i))].value, tree_[RightChild(static_cast<size_t>(i))].value);
    }
  }
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
size_t SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::RightChild(const size_t& parent) const {
  return (parent < (new_size_segment_ - 1) ? (2 * parent + 2) : 0);
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
size_t SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::LeftChild(const size_t& parent) const {
  return (parent < (new_size_segment_ - 1) ? (2 * parent + 1) : 0);
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
T SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::Query(const size_t& curr_node,
                                                                              const size_t& left_covered,
                                                                              const size_t& right_covered,
                                                                              const size_t& left, const size_t& right) {
  if ((left <= left_covered) && (right_covered <= right)) {
    return UpdateOp(tree_[curr_node].value, tree_[curr_node].promise);
  }
  if ((right_covered < left) || (left_covered > right)) {
    return DefaultOperation;
  }
  Push(curr_node);
  T left_result = Query(LeftChild(curr_node), left_covered, (right_covered + left_covered) / 2, left, right);
  T right_result = Query(RightChild(curr_node), (right_covered + left_covered) / 2 + 1, right_covered, left, right);
  return Operation(left_result, right_result);
}

template <typename T, T(Operation)(const T&, const T&), T DefaultOperation, T(UpdateOp)(const T&, const T&),
          T DefaultUpdate>
T SegmentTree<T, Operation, DefaultOperation, UpdateOp, DefaultUpdate>::Query(const size_t& left, const size_t& right) {
  return Query(0, 0, new_size_segment_ - 1, left, right);
}

size_t Max(const size_t& value1, const size_t& value2) {
  return std::max(value1, value2);
}
size_t Sum(const size_t& value1, const size_t& value2) {
  return value1 + value2;
}

void Requests(SegmentTree<size_t, Max, 0, Sum, 0>& hives) {
  size_t left = 0;
  size_t right = 0;
  size_t add = 0;
  size_t count_requests = 0;
  char type = 0;
  std::cin >> count_requests;
  for (size_t i = 0; i < count_requests; ++i) {
    std::cin >> type >> left >> right;
    if (type == 'm') {
      std::cout << hives.Query(left - 1, right - 1) << ' ';
    } else {
      std::cin >> add;
      hives.Update(left - 1, right - 1, add);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  SegmentTree<size_t, Max, 0, Sum, 0> hives;
  Requests(hives);
  return 0;
}
