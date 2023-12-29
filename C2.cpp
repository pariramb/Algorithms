#include <string>
#include <iostream>
#include <vector>

void StringInit(std::string& string) {
  std::cin >> string;
}

void ZFunc(std::string& string) {
  std::vector<size_t> z_func(string.size(), 0);
  size_t l = 0;
  size_t r = 0;
  auto str_size = string.size();
  for (size_t i = 1; i < str_size; ++i) {
    if (i < r) {
      z_func[i] = std::min(z_func[i - l], r - i);
    }
    while (i + z_func[i] < str_size && string[z_func[i]] == string[i + z_func[i]]) {
      ++z_func[i];
    }
    if (r < i + z_func[i]) {
      l = i;
      r = i + z_func[i];
    }
  }
  std::cout << str_size << ' ';
  for (size_t i = 1; i < str_size; ++i) {
    std::cout << z_func[i] << ' ';
  }
}

int main() {
  std::string string;
  StringInit(string);
  ZFunc(string);
  return 0;
}
