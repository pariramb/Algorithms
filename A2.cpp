#include <string>
#include <iostream>
#include <vector>

void StringInit(std::string& string) {
  std::cin >> string;
}

void PrefixFunc(std::string& string) {
  std::vector<size_t> prefix_func(string.size(), 0);
  for (size_t i = 1, size = string.size(), prev_val = 0; i < size; ++i) {
    prev_val = prefix_func[i - 1];
    while (string[i] != string[prev_val] && prev_val > 0) {
      prev_val = prefix_func[prev_val - 1];
    }
    if (string[i] == string[prev_val]) {
      prefix_func[i] = prev_val + 1;
    }
  }
  for (size_t i = 0, size = string.size(); i < size; ++i) {
    std::cout << prefix_func[i] << ' ';
  }
}

int main() {
  std::string string;
  StringInit(string);
  PrefixFunc(string);
  return 0;
}
