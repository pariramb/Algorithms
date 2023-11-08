#include <iostream>
#include <vector>

template <typename T, typename U>
class Treap {
  size_t size_;
  struct Coordinate {
    T x;
    U y;
  };
  struct Node {
    Coordinate coord;
    Node* parent;
    Node* right;
    Node* left;
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
      const int64_t no_node = 0;
      Node* parent = node.parent;
      Node* left = node.left;
      Node* right = node.right;
      if (parent) {
        os << parent->coord.x + 1 << ' ';
      } else {
        os << no_node << ' ';
      }
      if (left) {
        os << left->coord.x + 1 << ' ';
      } else {
        os << no_node << ' ';
      }
      if (right) {
        os << right->coord.x + 1;
      } else {
        os << no_node;
      }
      os << '\n';
      return os;
    }
    friend std::istream& operator>>(std::istream& is, Node& node) {
      is >> node.coord.x >> node.coord.y;
      node.left = node.right = node.parent = nullptr;
      return is;
    }
  };
  Node* root_;
  std::vector<Node*> order_;
  void Clear(Node*);

 public:
  Treap();
  void Result();
  ~Treap();
};

template <typename T, typename U>
Treap<T, U>::Treap() {
  std::cin >> size_;
  order_.resize(size_);
  Node* last_inserted = nullptr;
  root_ = nullptr;
  Node* curr = nullptr;
  Node* node = nullptr;
  for (size_t i = 0; i < size_; ++i) {
    node = new Node();
    std::cin >> *node;
    node->coord.x = i;
    curr = last_inserted;
    while (curr && node->coord.y < curr->coord.y) {
      curr = curr->parent;
    }
    if (curr == nullptr) {
      node->left = root_;
      if (root_) {
        root_->parent = node;
      }
      root_ = node;
    } else {
      node->left = curr->right;
      if (curr->right) {
        curr->right->parent = node;
      }
      curr->right = node;
      node->parent = curr;
    }
    last_inserted = node;
    order_[i] = node;
  }
}

template <typename T, typename U>
void Treap<T, U>::Clear(Node* curr) {
  if (curr->left) {
    Clear(curr->left);
  }
  if (curr->right) {
    Clear(curr->right);
  }
  delete curr;
}

template <typename T, typename U>
Treap<T, U>::~Treap() {
  Clear(root_);
}

template <typename T, typename U>
void Treap<T, U>::Result() {
  std::cout << "YES" << '\n';
  for (size_t i = 0; i < size_; ++i) {
    std::cout << *order_[i];
  }
}

int main() {
  Treap<int64_t, int64_t> outfits;
  outfits.Result();
}
