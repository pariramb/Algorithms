#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <queue>

class SuffixAutomaton {
  struct Node {
    std::unordered_map<char, std::shared_ptr<Node>> transitions;
    std::weak_ptr<Node> suffix;
    size_t length;
    size_t end_pos;
    size_t ind;
    bool visit;
    Node() : length(0), end_pos(0), ind(0), visit(false) {
    }
  };
  using PtrType = std::shared_ptr<Node>;
  PtrType start_;
  PtrType last_;
  size_t counter_;
  void AddSymbol(char);
  PtrType Clone(PtrType, char, PtrType);

 public:
  explicit SuffixAutomaton(const std::string&);
  size_t CountStates() const;
  void AllAutomaton() const;
};

void SuffixAutomaton::AllAutomaton() const {
  if (!start_) {
    return;
  }
  std::queue<std::shared_ptr<Node>> nodes;
  nodes.push(start_);
  start_->visit = true;
  while (!nodes.empty()) {
    auto tmp = nodes.front();
    nodes.pop();
    for (auto& node : tmp->transitions) {
      std::cout << tmp->ind << ' ' << node.first << ' ' << node.second->ind << '\n';
      if (!node.second->visit) {
        nodes.push(node.second);
        node.second->visit = true;
      }
    }
  }
}

size_t SuffixAutomaton::CountStates() const {
  return counter_;
}

SuffixAutomaton::SuffixAutomaton(const std::string& string)
    : start_(std::make_shared<Node>()), last_(start_), counter_(1) {
  for (size_t i = 0; i < string.size(); ++i) {
    AddSymbol(string[i]);
  }
}

void SuffixAutomaton::AddSymbol(char symbol) {
  PtrType new_node = std::make_shared<Node>();
  ++counter_;
  new_node->ind = counter_ - 1;
  new_node->length = last_->length + 1;
  new_node->end_pos = last_->end_pos + 1;
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
  last_ = new_node;
}

SuffixAutomaton::PtrType SuffixAutomaton::Clone(PtrType parent, char symbol, PtrType node) {
  PtrType clone = std::make_shared<Node>();
  ++counter_;
  clone->ind = counter_ - 1;
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

void Result(const SuffixAutomaton& suf_aut) {
  std::cout << suf_aut.CountStates() << '\n';
  suf_aut.AllAutomaton();
}

int main() {
  std::string string;
  std::cin >> string;
  SuffixAutomaton suf_aut(string);
  Result(suf_aut);
  return 0;
}
