#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Bor {
  struct Node {
    std::unordered_map<char, Node*> children;
    bool is_terminal;
    Node();
    ~Node();
  };
  Node* root_;

 public:
  Bor();
  bool Find(const std::string&);
  void Insert(const std::string&);
  void Clear();
  ~Bor();
};

Bor::Node::~Node() {
  for (auto& pair : children) {
    delete pair.second;
  }
}

Bor::Node::Node() : is_terminal(false) {
}

Bor::Bor() : root_(nullptr) {
}

bool Bor::Find(const std::string& string) {
  if (!root_) {
    return false;
  }
  auto cur = root_;
  auto next = root_->children.begin();
  for (auto& symbol : string) {
    next = cur->children.find(symbol);
    if (next == cur->children.end()) {
      return false;
    }
    cur = next->second;
  }
  return cur->is_terminal;
}

void Bor::Insert(const std::string& string) {
  if (!root_) {
    root_ = new Node();
  }
  auto cur = root_;
  Node* tmp = nullptr;
  bool flag = false;
  auto next = cur->children.end();
  for (auto& symbol : string) {
    if (!flag) {
      next = cur->children.find(symbol);
    }
    if (next == cur->children.end()) {
      flag = true;
      tmp = new Node();
      cur->children.insert({symbol, tmp});
      cur = tmp;
    } else {
      cur = next->second;
    }
  }
  cur->is_terminal = true;
}

Bor::~Bor() {
  Clear();
}

void Bor::Clear() {
  delete root_;
}

void Result() {
  Bor bor;
  std::string action;
  std::string string;
  std::cin >> action;
  while (action != "#") {
    std::cin >> string;
    if (action == "+") {
      bor.Insert(string);
    }
    if (action == "?") {
      if (bor.Find(string)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
    std::cin >> action;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Result();
  return 0;
}
