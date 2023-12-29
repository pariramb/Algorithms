#include <string>
#include <iostream>
#include <vector>

const char kFirstLetter = 'a';
const char kLastLetter = 'z';

void ZFuncInit(size_t& str_size, std::vector<int>& z_func) {
  std::cin >> str_size;
  z_func.resize(str_size, 0);
  for (size_t i = 0; i < str_size; ++i) {
    std::cin >> z_func[i];
  }
  z_func[0] = 0;
}

void ZToPrefix(std::vector<int>& prefix_func, std::vector<int>& z_func, const size_t& str_size) {
  prefix_func.resize(str_size, 0);
  for (size_t i = 0; i < str_size; ++i) {
    for (int delta = z_func[i] - 1; delta >= 0; --delta) {
      if (prefix_func[i + delta]) {
        break;
      }
      prefix_func[i + delta] = delta + 1;
    }
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
  std::vector<int> prefix_func;
  std::vector<int> z_func;
  size_t str_size = 0;
  ZFuncInit(str_size, z_func);
  ZToPrefix(prefix_func, z_func, str_size);
  RestoreStringPrefixFunc(string, prefix_func, str_size);
  return 0;
}
