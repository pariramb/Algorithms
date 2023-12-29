#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <queue>

class SuffixAutomaton {
  struct Node {
    std::unordered_map<char, std::shared_ptr<Node>> transitions;
    std::weak_ptr<Node> suffix;
    int length;
    size_t res;
    Node() : length(0), res(0) {
    }
  };
  using PtrType = std::shared_ptr<Node>;
  PtrType start_;
  PtrType last_;
  PtrType Clone(PtrType, char, PtrType);

 public:
  void AddSymbol(char);
  explicit SuffixAutomaton(const std::string&);
  bool CheckUnique(const int&) const;
};

bool SuffixAutomaton::CheckUnique(const int& size) const {
  return (last_->suffix.lock()->length < size);
}

SuffixAutomaton::SuffixAutomaton(const std::string& string) : start_(std::make_shared<Node>()), last_(start_) {
  for (size_t i = 0; i < string.size(); ++i) {
    AddSymbol(string[i]);
  }
}

void SuffixAutomaton::AddSymbol(char symbol) {
  PtrType new_node = std::make_shared<Node>();
  new_node->length = last_->length + 1;
  auto tmp = last_->res;
  while (last_ && last_->transitions.find(symbol) == last_->transitions.end()) {
    last_->transitions[symbol] = new_node;
    last_ = last_->suffix.lock();
  }
  if (!last_) {
    new_node->suffix = start_;
  } else if (last_->length + 1 == last_->transitions[symbol]->length) {
    new_node->suffix = last_->transitions[symbol];
  } else {
    new_node->suffix = Clone(last_, symbol, last_->transitions[symbol]);
  }
  new_node->res = new_node->length + tmp - new_node->suffix.lock()->length;
  std::cout << new_node->res << '\n';
  last_ = new_node;
}

SuffixAutomaton::PtrType SuffixAutomaton::Clone(PtrType parent, char symbol, PtrType node) {
  PtrType clone = std::make_shared<Node>();
  clone->transitions = node->transitions;
  clone->suffix = node->suffix;
  clone->length = parent->length + 1;
  node->suffix = clone;
  while (parent && parent->transitions[symbol] == node) {
    parent->transitions[symbol] = clone;
    parent = parent->suffix.lock();
  }
  return clone;
}

int main() {
  std::string string;
  std::cin >> string;
  SuffixAutomaton suf_aut(string);
  return 0;
}
