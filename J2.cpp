#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

void StringInit(std::string& word, std::string& result_word) {
  std::cin >> word;
  std::cin >> result_word;
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
  std::string word;
  std::string result_word;
  StringInit(word, result_word);
  std::string string = word + "#" + result_word;
  std::vector<size_t> z_func(string.size(), 0);
  ZFunc(string, z_func);
  std::deque<size_t> partition;
  partition.push_back(word.size() + 1);
  for (size_t i = word.size() + 1; i < string.size(); ++i) {
    if (z_func[i] == 0) {
      if (z_func[partition.back()] + partition.back() <= i) {
        std::cout << "Yes";
        return;
      }
    } else {
      if (z_func[partition.back()] + partition.back() < i + z_func[i]) {
        partition.push_back(i);
      }
    }
  }
  std::cout << "No\n";
  size_t ind = word.size() + 1;
  partition.pop_front();
  for (auto value : partition) {
    std::cout << string.substr(ind, value - ind) << " ";
    ind = value;
  }
  std::cout << string.substr(ind);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Result();
  return 0;
}
