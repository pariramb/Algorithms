#include <iostream>
#include <vector>
#include <random>

template <typename Key>
class Treap {
  struct Coordinate {
    Key x;
    size_t y;
    explicit Coordinate(const Key& x) : x(x) {
      y = std::rand();
    }
  };
  struct Node {
    Coordinate coord;
    Key result;
    Node* parent;
    Node* right;
    Node* left;
    size_t size;
    explicit Node(const Key& key) : coord(key), result(key), parent(nullptr), right(nullptr), left(nullptr), size(1) {
    }
  };
  Node* root_;
  void Clear(Node*);
  Node* Merge(Node*, Node*);
  bool Find(const Node*, const Key&) const;
  std::pair<Node*, Node*> Split(Node*, const Key& key);
  void FixNode(Node* node);
  int Size(Node*) const;
  Key Result(Node* node) const;

 public:
  Treap() : root_(nullptr) {
  }
  void Insert(const Key&);
  bool Find(const Key&) const;
  const Node* Next(const Key&);
  Key RMQ(const Key&, const Key&);
  ~Treap();
};

template <typename Key>
Key Treap<Key>::RMQ(const Key& left, const Key& right) {
  auto roots1 = Split(root_, left);
  auto roots2 = Split(roots1.second, right);
  auto result = Result(roots2.first);
  root_ = Merge(Merge(roots1.first, roots2.first), roots2.second);
  return result;
}

template <typename Key>
Key Treap<Key>::Result(Treap<Key>::Node* node) const {
  return (node ? node->result : 0);
}

template <typename Key>
void Treap<Key>::FixNode(Treap<Key>::Node* node) {
  if (node) {
    node->size = 1 + Size(node->left) + Size(node->right);
    node->result = Result(node->left) + node->coord.x + Result(node->right);
  }
}

template <typename Key>
int Treap<Key>::Size(Treap<Key>::Node* node) const {
  return (node ? node->size : 0);
}

template <typename Key>
const typename Treap<Key>::Node* Treap<Key>::Next(const Key& key) {
  Node* cur = root_;
  Node* next = nullptr;
  while (cur) {
    if (cur->coord.x > key) {
      next = cur;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return next;
}

template <typename Key>
bool Treap<Key>::Find(const Key& key) const {
  return Find(root_, key);
}

template <typename Key>
bool Treap<Key>::Find(const Node* node, const Key& key) const {
  if (!node) {
    return false;
  }
  if (node->coord.x == key) {
    return true;
  }
  if (key > node->coord.x) {
    return Find(node->right, key);
  }
  return Find(node->left, key);
}

template <typename Key>
void Treap<Key>::Insert(const Key& key) {
  if (Find(key)) {
    return;
  }
  auto roots = Split(root_, key);
  Node* node = new Node(key);
  root_ = Merge(Merge(roots.first, node), roots.second);
}

template <typename Key>
std::pair<typename Treap<Key>::Node*, typename Treap<Key>::Node*> Treap<Key>::Split(Treap<Key>::Node* root,
                                                                                    const Key& key) {
  if (!root) {
    return std::make_pair(nullptr, nullptr);
  }
  if (root->coord.x < key) {
    auto roots = Split(root->right, key);
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
  auto roots = Split(root->left, key);
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

template <typename Key>
typename Treap<Key>::Node* Treap<Key>::Merge(Node* root1, Node* root2) {
  if (!root1) {
    return root2;
  }
  if (!root2) {
    return root1;
  }
  if (root1->coord.y < root2->coord.y) {
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

template <typename Key>
void Treap<Key>::Clear(Node* curr) {
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

template <typename Key>
Treap<Key>::~Treap() {
  Clear(root_);
}

void Answers(Treap<int64_t>& moods) {
  size_t commands_count = 0;
  std::cin >> commands_count;
  char command = 0;
  int value = 0;
  int64_t left = 0;
  int64_t right = 0;
  for (size_t i = 0; i < commands_count; ++i) {
    std::cin >> command;
    if (command == '+') {
      std::cin >> value;
      moods.Insert(value);
      continue;
    }
    if (command == '?') {
      std::cin >> left;
      std::cin >> right;
      std::cout << moods.RMQ(left, right + 1) << '\n';
      continue;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Treap<int64_t> moods;
  Answers(moods);
}
