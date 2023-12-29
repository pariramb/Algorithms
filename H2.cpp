#include <string>
#include <iostream>
#include <vector>

size_t ZFunc(std::string& string, size_t str_to_join_size) {
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
  for (size_t i = str_size - str_to_join_size, j = 0; i < str_size; ++i, ++j) {
    if (z_func[i] == str_to_join_size - j) {
      return z_func[i];
    }
  }
  return 0;
}

void Result() {
  size_t count = 0;
  std::cin >> count;
  std::string string1;
  std::string string2;
  std::string string3;
  std::cin >> string1;
  size_t delete_substr = 0;
  for (size_t i = 1; i < count; ++i) {
    std::cin >> string2;
    if (string1.size() >= string2.size()) {
      string3 = string2;
      string3 += string1.substr(string1.size() - string2.size());
      delete_substr = ZFunc(string3, string2.size());
    } else {
      string3 = string2.substr(0, string1.size());
      string3 += string1;
      delete_substr = ZFunc(string3, string1.size());
    }
    string2 = string2.substr(delete_substr);
    string1 += string2;
  }
  std::cout << string1;
}

int main() {
  Result();
  return 0;
}
