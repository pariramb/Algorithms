#include <string>
#include <iostream>
#include <vector>

void StringInit(std::string& string_before, std::string& string_after) {
  std::cin >> string_before;
  std::cin >> string_after;
}

size_t ZFunc(const std::string& string, std::vector<size_t>& z_func) {
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
  return 0;
}

void Result() {
  size_t count = 0;
  std::cin >> count;
  count -= 1;
  std::string string_before;
  std::string string_after;
  StringInit(string_before, string_after);
  std::string string = string_before + string_after;
  std::vector<size_t> z_func1(string.size(), 0);
  ZFunc(string, z_func1);
  string = string_after + string_before;
  std::vector<size_t> z_func2(string.size(), 0);
  ZFunc(string, z_func2);
  if (z_func1[count] == count) {
    std::cout << "Random";
    return;
  }
  bool shoot = false;
  bool flag = false;
  for (size_t i = count + 1, j = 1; i < 2 * count; ++i, ++j) {
    if ((z_func1[i] == 2 * count - i) && (z_func1[i] == count - 1 || z_func2[2 * count - j + 1] == j - 1)) {
      if (!flag) {
        if (string_before[2 * count - i] == '1') {
          shoot = true;
        }
        flag = true;
      } else {
        if ((shoot && string_before[2 * count - i] == '0') || (!shoot && string_before[2 * count - i] == '1')) {
          std::cout << "Random";
          return;
        }
      }
    }
  }
  if (shoot) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }
}

int main() {
  Result();
  return 0;
}
