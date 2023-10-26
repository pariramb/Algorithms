#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

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
  Treap() : root_(nullptr) {
  }
  void Insert(const size_t& k, const T&);
  T RMQ(const size_t&, const size_t&);
  ~Treap();
};

template <typename T, T Default>
T Treap<T, Default>::RMQ(const size_t& left, const size_t& right) {
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
    node->result = std::min(std::min(Result(node->left), node->value), Result(node->right));
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

void Answers(Treap<int, INT32_MAX>& moods) {
  size_t commands_count = 0;
  std::cin >> commands_count;
  char command = 0;
  size_t left = 0;
  size_t right = 0;
  int value = 0;
  for (size_t i = 0; i < commands_count; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> left >> value;
      moods.Insert(left, value);
      continue;
    }
    if (command == '?') {
      std::cin >> left;
      std::cin >> right;
      std::cout << moods.RMQ(left - 1, right) << '\n';
      continue;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Treap<int, INT32_MAX> moods;
  Answers(moods);
}
