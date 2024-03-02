#include <iostream>
#include <vector>
#include <random>
#include <cstring>

template <typename T, typename U>
class Treap {
  struct Coordinate {
    T x;
    U y;
    explicit Coordinate(const T& x) : x(x) {
      const U max_value = 10e5;
      std::random_device rd;
      std::mt19937 gen(rd());
      y = gen() % max_value;
    }
  };
  struct Node {
    Coordinate coord;
    Node* parent;
    Node* right;
    Node* left;
    size_t size;
    explicit Node(const T& mood) : coord(mood), parent(nullptr), right(nullptr), left(nullptr), size(1) {
    }
  };
  Node* root_;
  void Clear(Node*);
  Node* Merge(Node*, Node*);
  bool Find(const Node*, const T&) const;
  std::pair<Node*, Node*> Split(Node*, const T& key);
  const typename Treap<T, U>::Node* Kth(Node*, int) const;
  void FixNode(Node* node);
  int Size(Node*) const;

 public:
  Treap() : root_(nullptr) {
  }
  void Insert(const T&);
  void Erase(const T&);
  bool Find(const T&) const;
  const Node* Next(const T&);
  const Node* Prev(const T&);
  const typename Treap<T, U>::Node* Kth(const int&) const;
  ~Treap();
};

template <typename T, typename U>
void Treap<T, U>::FixNode(Treap<T, U>::Node* node) {
  if (node) {
    node->size = 1 + Size(node->left) + Size(node->right);
  }
}

template <typename T, typename U>
int Treap<T, U>::Size(Treap<T, U>::Node* node) const {
  return (node ? node->size : 0);
}

template <typename T, typename U>
const typename Treap<T, U>::Node* Treap<T, U>::Kth(Treap<T, U>::Node* node, int k) const {
  if (Size(node) < k + 1) {
    return nullptr;
  }
  while (true) {
    if (Size(node->left) < k) {
      k -= Size(node->left) + 1;
      node = node->right;
    } else if (Size(node->left) > k) {
      node = node->left;
    } else {
      return node;
    }
  }
  return nullptr;
}

template <typename T, typename U>
const typename Treap<T, U>::Node* Treap<T, U>::Kth(const int& k) const {
  return Kth(root_, k);
}

template <typename T, typename U>
const typename Treap<T, U>::Node* Treap<T, U>::Next(const T& mood) {
  Node* cur = root_;
  Node* next = nullptr;
  while (cur) {
    if (cur->coord.x > mood) {
      next = cur;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return next;
}

template <typename T, typename U>
const typename Treap<T, U>::Node* Treap<T, U>::Prev(const T& mood) {
  auto roots = Split(root_, mood);
  if (!roots.first) {
    root_ = Merge(roots.first, roots.second);
    return nullptr;
  }
  Node* node = roots.first;
  while (node->right) {
    node = node->right;
  }
  root_ = Merge(roots.first, roots.second);
  return node;
}

template <typename T, typename U>
bool Treap<T, U>::Find(const T& mood) const {
  return Find(root_, mood);
}

template <typename T, typename U>
bool Treap<T, U>::Find(const Node* node, const T& mood) const {
  if (!node) {
    return false;
  }
  if (node->coord.x == mood) {
    return true;
  }
  if (mood > node->coord.x) {
    return Find(node->right, mood);
  }
  return Find(node->left, mood);
}

template <typename T, typename U>
void Treap<T, U>::Erase(const T& mood) {
  if (!Find(mood)) {
    return;
  }
  auto roots1 = Split(root_, mood);
  auto node = Next(mood);
  T key = mood + 1;
  if (node) {
    key = node->coord.x;
  }
  auto roots2 = Split(roots1.second, key);
  delete roots2.first;
  root_ = Merge(roots1.first, roots2.second);
}

template <typename T, typename U>
void Treap<T, U>::Insert(const T& mood) {
  if (Find(mood)) {
    return;
  }
  auto roots = Split(root_, mood);
  Node* node = new Node(mood);
  root_ = Merge(Merge(roots.first, node), roots.second);
}

template <typename T, typename U>
std::pair<typename Treap<T, U>::Node*, typename Treap<T, U>::Node*> Treap<T, U>::Split(Treap<T, U>::Node* root,
                                                                                       const T& key) {
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

template <typename T, typename U>
typename Treap<T, U>::Node* Treap<T, U>::Merge(Node* root1, Node* root2) {
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

template <typename T, typename U>
void Treap<T, U>::Clear(Node* curr) {
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

template <typename T, typename U>
Treap<T, U>::~Treap() {
  Clear(root_);
}

void Result(Treap<int, int>& moods) {
  const size_t k_max_len = 10;
  char command[k_max_len];
  int value = 0;
  while (std::cin >> command) {
    std::cin >> value;
    if (!std::strcmp(command, "insert")) {
      moods.Insert(value);
      continue;
    }
    if (!std::strcmp(command, "delete")) {
      moods.Erase(value);
      continue;
    }
    if (!std::strcmp(command, "exists")) {
      if (moods.Find(value)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
      continue;
    }
    if (!std::strcmp(command, "next")) {
      auto result = moods.Next(value);
      if (result) {
        std::cout << result->coord.x << "\n";
      } else {
        std::cout << "none\n";
      }
      continue;
    }
    if (!std::strcmp(command, "prev")) {
      auto result = moods.Prev(value);
      if (result) {
        std::cout << result->coord.x << "\n";
      } else {
        std::cout << "none\n";
      }
      continue;
    }
    if (!std::strcmp(command, "kth")) {
      auto result = moods.Kth(value);
      if (result) {
        std::cout << result->coord.x << "\n";
      } else {
        std::cout << "none\n";
      }
    }
  }
}

int main() {
  Treap<int, int> moods;
  Result(moods);
}
