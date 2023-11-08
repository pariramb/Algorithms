#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
class TwoTrees;

template <typename T, T Default>
class Treap {
  struct Node {
    size_t prior;
    T value;
    T result;
    Node* parent;
    Node* right;
    Node* left;
    size_t size;
    explicit Node(const T& value)
        : value(value), result(value), parent(nullptr), right(nullptr), left(nullptr), size(1) {
      const size_t max_value = 10e9;
      std::random_device rd;
      std::mt19937 gen(rd());
      prior = gen() % max_value;
    }
  };
  Node* root_;
  void Clear(Node*);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Split(Node*, const size_t&);
  void FixNode(Node* node);
  size_t Size(Node*) const;
  T Result(Node* node) const;

 public:
  Treap(const size_t& size, std::vector<int64_t>::const_iterator);
  void Insert(const size_t& k, const T&);
  T RSQ(const size_t&, const size_t&);
  ~Treap();
  friend TwoTrees;
};

template <typename T, T Default>
Treap<T, Default>::Treap(const size_t& size, std::vector<int64_t>::const_iterator array) : root_(nullptr) {
  for (size_t i = 0; i < size; ++i) {
    Insert(i, *(array + static_cast<int64_t>(i) * 2));
  }
}

template <typename T, T Default>
T Treap<T, Default>::RSQ(const size_t& left, const size_t& right) {
  auto roots1 = Split(root_, left);
  auto roots2 = Split(roots1.second, right - left);
  auto result = Result(roots2.first);
  root_ = Merge(Merge(roots1.first, roots2.first), roots2.second);
  return result;
}

template <typename T, T Default>
T Treap<T, Default>::Result(Node* node) const {
  return (node ? node->result : Default);
}

template <typename T, T Default>
void Treap<T, Default>::FixNode(Node* node) {
  if (node) {
    node->size = 1 + Size(node->left) + Size(node->right);
    node->result = Result(node->left) + node->value + Result(node->right);
  }
}

template <typename T, T Default>
size_t Treap<T, Default>::Size(Node* node) const {
  return (node ? node->size : 0);
}

template <typename T, T Default>
void Treap<T, Default>::Insert(const size_t& k, const T& value) {
  auto roots = Split(root_, k);
  Node* node = new Node(value);
  root_ = Merge(Merge(roots.first, node), roots.second);
}

template <typename T, T Default>
std::pair<typename Treap<T, Default>::Node*, typename Treap<T, Default>::Node*> Treap<T, Default>::Split(
    Node* root, const size_t& k) {
  if (!root) {
    return std::make_pair(nullptr, nullptr);
  }
  if (Size(root->left) < k) {
    auto roots = Split(root->right, k - Size(root->left) - 1);
    root->right = roots.first;
    if (roots.first) {
      roots.first->parent = root;
    }
    if (roots.second) {
      roots.second->parent = nullptr;
    }
    FixNode(root);
    return std::make_pair(root, roots.second);
  }
  auto roots = Split(root->left, k);
  root->left = roots.second;
  if (roots.second) {
    roots.second->parent = root;
  }
  if (roots.first) {
    roots.first->parent = nullptr;
  }
  FixNode(root);
  return std::make_pair(roots.first, root);
}

template <typename T, T Default>
typename Treap<T, Default>::Node* Treap<T, Default>::Merge(Node* root1, Node* root2) {
  if (!root1) {
    return root2;
  }
  if (!root2) {
    return root1;
  }
  if (root1->prior < root2->prior) {
    root2->left = Merge(root1, root2->left);
    if (root2->left) {
      root2->left->parent = root2;
    }
    FixNode(root2);
    return root2;
  }
  root1->right = Merge(root1->right, root2);
  if (root1->right) {
    root1->right->parent = root1;
  }
  FixNode(root1);
  return root1;
}

template <typename T, T Default>
void Treap<T, Default>::Clear(Node* curr) {
  if (curr) {
    if (curr->left) {
      Clear(curr->left);
    }
    if (curr->right) {
      Clear(curr->right);
    }
  }
  delete curr;
}

template <typename T, T Default>
Treap<T, Default>::~Treap() {
  Clear(root_);
}

class TwoTrees {
  Treap<int64_t, 0> first_;
  Treap<int64_t, 0> second_;

 public:
  TwoTrees(const size_t& size, std::vector<int64_t>& array)
      : first_((size % 2 ? size / 2 + 1 : size / 2), array.cbegin()), second_(size / 2, array.cbegin() + 1) {
  }
  void Swap(const size_t&, const size_t&);
  int64_t RSQ(const size_t&, const size_t&);
};

void TwoTrees::Swap(const size_t& left, const size_t& right) {  // 0 инд
  size_t ind_left = left / 2;
  size_t ind_right = right / 2;
  using Pair = std::pair<Treap<int64_t, 0>::Node*, Treap<int64_t, 0>::Node*>;
  Pair roots1_fir;
  Pair roots2_sec;
  Pair roots2_fir;
  auto roots1_sec = second_.Split(second_.root_, ind_left);
  if (left % 2) {
    roots1_fir = first_.Split(first_.root_, ind_left + 1);
    roots2_sec = second_.Split(roots1_sec.second, ind_right - ind_left);
    roots2_fir = first_.Split(roots1_fir.second, ind_right + 1 - ind_left - 1);
  } else {
    roots1_fir = first_.Split(first_.root_, ind_left);
    roots2_sec = second_.Split(roots1_sec.second, ind_right + 1 - ind_left);
    roots2_fir = first_.Split(roots1_fir.second, ind_right + 1 - ind_left);
  }
  first_.root_ = first_.Merge(first_.Merge(roots1_fir.first, roots2_sec.first), roots2_fir.second);
  second_.root_ = second_.Merge(second_.Merge(roots1_sec.first, roots2_fir.first), roots2_sec.second);
}

int64_t TwoTrees::RSQ(const size_t& left, const size_t& right) {
  if (left % 2) {
    if (right % 2) {
      return first_.RSQ(left / 2 + 1, right / 2 + 1) + second_.RSQ(left / 2, right / 2 + 1);
    }
    return first_.RSQ(left / 2 + 1, right / 2 + 1) + second_.RSQ(left / 2, right / 2);
  }
  if (right % 2) {
    return first_.RSQ(left / 2, right / 2 + 1) + second_.RSQ(left / 2, right / 2 + 1);
  }
  return first_.RSQ(left / 2, right / 2 + 1) + second_.RSQ(left / 2, right / 2);
}

void Requests() {
  size_t size = 0;
  size_t swapper_num = 1;
  size_t count_commands = 0;
  std::cin >> size >> count_commands;
  while (size || count_commands) {
    std::cout << "Swapper " << swapper_num++ << ":"
              << "\n";
    std::vector<int64_t> values(size);
    for (size_t i = 0; i < size; ++i) {
      std::cin >> values[i];
    }
    TwoTrees trees(size, values);
    size_t left = 0;
    size_t right = 0;
    int command = 0;
    for (size_t i = 0; i < count_commands; ++i) {
      std::cin >> command >> left >> right;
      if (command == 1) {
        trees.Swap(left - 1, right - 1);
      } else {
        std::cout << trees.RSQ(left - 1, right - 1) << "\n";
      }
    }
    std::cin >> size >> count_commands;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Requests();
}
