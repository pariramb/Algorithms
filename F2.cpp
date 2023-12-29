#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void StringInit(std::string& string) {
  std::cin >> string;
}

size_t ZFunc(std::string& string, const size_t& size) {
  std::reverse(string.begin(), string.begin() + static_cast<int>(size));
  std::vector<size_t> z_func(size, 0);
  size_t l = 0;
  size_t r = 0;
  size_t max_pref = 0;
  for (size_t i = 1; i < size; ++i) {
    if (i < r) {
      z_func[i] = std::min(z_func[i - l], r - i);
    }
    while (i + z_func[i] < size && string[z_func[i]] == string[i + z_func[i]]) {
      ++z_func[i];
    }
    max_pref = std::max(max_pref, z_func[i]);
    if (r < i + z_func[i]) {
      l = i;
      r = i + z_func[i];
    }
  }
  std::reverse(string.begin(), string.begin() + static_cast<int>(size));
  return size - max_pref;
}
void CountSubstrings(std::string& string) {
  size_t count = 1;
  for (size_t i = 2; i <= string.size(); ++i) {
    count += ZFunc(string, i);
  }
  std::cout << count;
}

int main() {
  std::string string;
  StringInit(string);
  CountSubstrings(string);
  return 0;
}
