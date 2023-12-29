#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void StringInit(std::vector<size_t>& string, const size_t& count) {
  for (size_t i = 0; i < count; ++i) {
    std::cin >> string[i];
    string[count + 1 + i] = string[i];
  }
  string[count] = 0;
  std::reverse(string.begin() + static_cast<int>(count) + 1, string.end());
}

void ZFunc(std::vector<size_t>& string, const size_t& count) {
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
  for (size_t i = 0; i < count; ++i) {
    size_t ind = count + 1 + i;
    if (!(z_func[ind] % 2) && (z_func[ind] + i >= count)) {
      std::cout << count - z_func[ind] / 2 << ' ';
    }
  }
  std::cout << count;
}

int main() {
  size_t count = 0;
  size_t count_col = 0;
  std::cin >> count >> count_col;
  std::vector<size_t> string(2 * count + 1);
  StringInit(string, count);
  ZFunc(string, count);
  return 0;
}
