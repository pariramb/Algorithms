#include <string>
#include <iostream>
#include <vector>

class KMP {
  std::string string_;
  std::string find_;
  std::vector<size_t> prefix_func_find_;
  void PrefixFuncString();
  void PrefixFuncFind();

 public:
  KMP();
  void StdoutInd();
};

KMP::KMP() {
  std::cin >> string_;
  std::cin >> find_;
  prefix_func_find_.resize(find_.size(), 0);
}

void KMP::StdoutInd() {
  PrefixFuncFind();
  PrefixFuncString();
}

void KMP::PrefixFuncString() {
  for (size_t i = 0, size = string_.size(), prev_val = 0; i < size; ++i) {
    while (string_[i] != find_[prev_val] && prev_val > 0) {
      prev_val = prefix_func_find_[prev_val - 1];
    }
    if (string_[i] == find_[prev_val]) {
      prev_val += 1;
      if (prev_val == find_.size()) {
        std::cout << i + 1 - find_.size() << '\n';
      }
    }
  }
}

void KMP::PrefixFuncFind() {
  for (size_t i = 1, size = find_.size(), prev_val = 0; i < size; ++i) {
    prev_val = prefix_func_find_[i - 1];
    while (find_[i] != find_[prev_val] && prev_val > 0) {
      prev_val = prefix_func_find_[prev_val - 1];
    }
    if (find_[i] == find_[prev_val]) {
      prefix_func_find_[i] = prev_val + 1;
    }
  }
}

int main() {
  KMP kmp;
  kmp.StdoutInd();
  return 0;
}
