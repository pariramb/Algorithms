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
    Node() : length(0) {
    }
  };
  using PtrType = std::shared_ptr<Node>;
  PtrType start_;
  PtrType last_;
  PtrType Clone(PtrType, char, PtrType);

 public:
  void AddSymbol(char);
  SuffixAutomaton();
  bool CheckUnique(const int&) const;
};

bool SuffixAutomaton::CheckUnique(const int& size) const {
  return (last_->suffix.lock()->length < size);
}

SuffixAutomaton::SuffixAutomaton() : start_(std::make_shared<Node>()), last_(start_) {
}

void SuffixAutomaton::AddSymbol(char symbol) {
  PtrType new_node = std::make_shared<Node>();
  new_node->length = last_->length + 1;
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

void Result(SuffixAutomaton& suf_aut) {
  char request = ' ';
  char symbol = ' ';
  int count = 0;
  int size = 0;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    std::cin >> request;
    if (request == '+') {
      std::cin >> symbol;
      suf_aut.AddSymbol(symbol);
    } else {
      std::cin >> size;
      if (suf_aut.CheckUnique(size)) {
        std::cout << "+\n";
      } else {
        std::cout << "-\n";
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  SuffixAutomaton suf_aut;
  Result(suf_aut);
  return 0;
}