#include <string>
#include <iostream>
#include <vector>

const char kFirstLetter = 'a';
const char kLastLetter = 'z';

void PrefixFuncInit(size_t& str_size, std::vector<int>& prefix_func) {
  std::cin >> str_size;
  prefix_func.resize(str_size);
  for (size_t i = 0; i < str_size; ++i) {
    std::cin >> prefix_func[i];
  }
}

void RestoreStringPrefixFunc(std::string& string, std::vector<int>& prefix_func, const size_t& str_size) {
  string.resize(str_size);
  string[0] = kFirstLetter;
  int pref_val = 0;
  for (size_t i = 1; i < str_size; ++i) {
    if (prefix_func[i]) {
      string[i] = string[prefix_func[i] - 1];
    } else {
      size_t banned_size = kLastLetter - kFirstLetter + 1;
      std::vector<bool> banned(banned_size, false);
      pref_val = prefix_func[i - 1];
      while (pref_val) {
        banned[string[pref_val] - kFirstLetter] = true;
        pref_val = prefix_func[pref_val - 1];
      }
      for (size_t j = 1; j < banned_size; ++j) {
        if (!banned[j]) {
          string[i] = static_cast<char>(kFirstLetter + j);
          break;
        }
      }
    }
  }
  std::cout << string;
}

int main() {
  std::string string;
  size_t str_size = 0;
  std::vector<int> prefix_func;
  PrefixFuncInit(str_size, prefix_func);
  RestoreStringPrefixFunc(string, prefix_func, str_size);
  return 0;
}
