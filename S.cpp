#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

template <typename T, T Default>
class TreapReverse {
  struct Node {
    bool reverse_flag;
    size_t prior;
    T value;
    T result;
    Node* parent;
    Node* right;
    Node* left;
    size_t size;
    explicit Node(const T& value)
        : reverse_flag(false), value(value), result(value), parent(nullptr), right(nullptr), left(nullptr), size(1) {
      prior = std::rand();
    }
  };
  Node* root_;
  void Clear(Node*);
  Node* Merge(Node*, Node*);
  std::pair<Node*, Node*> Split(Node*, const size_t&);
  void FixNode(Node* node);
  size_t Size(Node*) const;
  T Result(Node* node) const;
  void Push(Node*);

 public:
  TreapReverse() : root_(nullptr) {
  }
  void Insert(const size_t& k, const T&);
  T RMQ(const size_t&, const size_t&);
  void Reverse(const size_t&, const size_t&);
  ~TreapReverse();
};

template <typename T, T Default>
void TreapReverse<T, Default>::Reverse(const size_t& left, const size_t& right) {
  auto roots1 = Split(root_, left);
  auto roots2 = Split(roots1.second, right - left);
  if (roots2.first) {
    roots2.first->reverse_flag = !roots2.first->reverse_flag;
  }
  root_ = Merge(Merge(roots1.first, roots2.first), roots2.second);
}

template <typename T, T Default>
void TreapReverse<T, Default>::Push(Node* node) {
  if (!node) {
    return;
  }
  if (node->reverse_flag) {
    auto left = node->left;
    auto right = node->right;
    if (left) {
      left->reverse_flag = !left->reverse_flag;
    }
    if (right) {
      right->reverse_flag = !right->reverse_flag;
    }
    node->left = right;
    node->right = left;
    node->reverse_flag = false;
  }
}

template <typename T, T Default>
T TreapReverse<T, Default>::RMQ(const size_t& left, const size_t& right) {
  auto roots1 = Split(root_, left);
  auto roots2 = Split(roots1.second, right - left);
  Push(roots2.first);
  auto result = Result(roots2.first);
  root_ = Merge(Merge(roots1.first, roots2.first), roots2.second);
  return result;
}

template <typename T, T Default>
T TreapReverse<T, Default>::Result(Node* node) const {
  return (node ? node->result : Default);
}

template <typename T, T Default>
void TreapReverse<T, Default>::FixNode(Node* node) {
  if (node) {
    node->size = 1 + Size(node->left) + Size(node->right);
    node->result = std::min(std::min(Result(node->left), node->value), Result(node->right));
  }
}

template <typename T, T Default>
size_t TreapReverse<T, Default>::Size(Node* node) const {
  return (node ? node->size : 0);
}

template <typename T, T Default>
void TreapReverse<T, Default>::Insert(const size_t& k, const T& value) {
  auto roots = Split(root_, k);
  Node* node = new Node(value);
  root_ = Merge(Merge(roots.first, node), roots.second);
}

template <typename T, T Default>
std::pair<typename TreapReverse<T, Default>::Node*, typename TreapReverse<T, Default>::Node*>
TreapReverse<T, Default>::Split(Node* root, const size_t& k) {
  if (!root) {
    return std::make_pair(nullptr, nullptr);
  }
  Push(root);
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
typename TreapReverse<T, Default>::Node* TreapReverse<T, Default>::Merge(Node* root1, Node* root2) {
  if (!root1) {
    return root2;
  }
  if (!root2) {
    return root1;
  }
  if (root1->prior < root2->prior) {
    Push(root2);
    root2->left = Merge(root1, root2->left);
    if (root2->left) {
      root2->left->parent = root2;
    }
    FixNode(root2);
    return root2;
  }
  Push(root1);
  root1->right = Merge(root1->right, root2);
  if (root1->right) {
    root1->right->parent = root1;
  }
  FixNode(root1);
  return root1;
}

template <typename T, T Default>
void TreapReverse<T, Default>::Clear(Node* curr) {
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
TreapReverse<T, Default>::~TreapReverse() {
  Clear(root_);
}

void Answers(TreapReverse<int, INT32_MAX>& array) {
  size_t commands_count = 0;
  size_t size = 0;
  std::cin >> size;
  std::cin >> commands_count;
  int el = 0;
  for (size_t i = 0; i < size; ++i) {
    std::cin >> el;
    array.Insert(i, el);
  }
  char command = 0;
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 0; i < commands_count; ++i) {
    std::cin >> command >> left >> right;
    if (command == '1') {
      array.Reverse(left - 1, right);
      continue;
    }
    if (command == '2') {
      std::cout << array.RMQ(left - 1, right) << '\n';
      continue;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  TreapReverse<int, INT32_MAX> array;
  Answers(array);
}
