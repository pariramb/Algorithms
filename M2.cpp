#include <cstring>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

class Trie {
 protected:
  static const size_t kSigmaSz = 26;

  struct Node {
    std::vector<int> to;
    bool term;
    std::vector<int> numbers;
    Node() {
      to = std::vector<int>(kSigmaSz, -1);
      term = false;
      numbers = std::vector<int>();
    }
  };

  std::vector<Node> tree_;

 public:
  void Add(const std::string& str, const int& number) {
    if (tree_.empty()) {
      tree_.emplace_back();
    }
    int vertex = 0;
    for (size_t i = 0; i < str.size(); ++i) {
      if (tree_[vertex].to[str[i] - 'a'] == -1) {
        tree_[vertex].to[str[i] - 'a'] = static_cast<int>(tree_.size());
        tree_.emplace_back();
      }
      vertex = tree_[vertex].to[str[i] - 'a'];
    }
    tree_[vertex].term = true;
    tree_[vertex].numbers.push_back(number);
  }
};

class AhoCorasik : public Trie {
 private:
  std::vector<int> link_;
  std::vector<std::array<int, kSigmaSz>> go_;
  std::vector<int> cnt_;
  std::vector<int> compressed_link_;

 public:
  void StartBFS() {
    std::queue<int> queue;
    queue.push(0);

    while (!queue.empty()) {
      int vertex = queue.front();
      queue.pop();
      for (size_t symbol = 0; symbol < kSigmaSz; ++symbol) {
        if (tree_[vertex].to[symbol] == -1) {
          continue;
        }

        int next = tree_[vertex].to[symbol];
        link_[next] = (vertex == 0 ? 0 : go_[link_[vertex]][symbol]);
        for (size_t symbol2 = 0; symbol2 < kSigmaSz; ++symbol2) {
          if (tree_[next].to[symbol2] != -1) {
            go_[next][symbol2] = tree_[next].to[symbol2];
          } else {
            go_[next][symbol2] = go_[link_[next]][symbol2];
          }
        }

        cnt_[next] = (tree_[next].term ? static_cast<int>(tree_[next].numbers.size()) : 0) + (cnt_[link_[next]]);
        compressed_link_[next] = (tree_[link_[next]].term ? link_[next] : compressed_link_[link_[next]]);
        queue.push(next);
      }
    }
  }

  void BuildAutomant() {
    link_ = std::vector<int>(tree_.size(), 0);
    compressed_link_ = std::vector<int>(tree_.size(), 0);
    cnt_ = std::vector<int>(tree_.size(), 0);
    go_ = std::vector<std::array<int, kSigmaSz>>(tree_.size());

    for (size_t symbol = 0; symbol < kSigmaSz; ++symbol) {
      if (tree_[0].to[symbol] != -1) {
        go_[0][symbol] = tree_[0].to[symbol];
      } else {
        go_[0][symbol] = 0;
      }
    }
    StartBFS();
  }

  void GiveAnswer(const std::string& text, const std::vector<std::string>& strings,
                  const std::vector<std::pair<size_t, size_t>>& ind) {
    std::vector<std::vector<int>> answer(strings.size());
    int v_i = 0;
    for (size_t j = 0; j < text.size(); ++j) {
      v_i = go_[v_i][text[j] - 'a'];
      int v_copy = v_i;
      while (v_copy != 0) {
        if (tree_[v_copy].term) {
          for (auto& index : tree_[v_copy].numbers) {
            answer[index].push_back(static_cast<int>(j + 2UL - strings[index].size()));
          }
        }
        v_copy = compressed_link_[v_copy];
      }
    }

    for (size_t i = 0; i < answer.size(); ++i) {
      if (ind[i].second - ind[i].first + 1 < strings[i].size() || answer[i].empty()) {
        std::cout << '-';
        continue;
      }
      size_t counter = 0;
      for (auto& index : answer[i]) {
        if (index >= static_cast<int>(ind[i].first) && index + strings[i].size() - 1 <= ind[i].second) {
          std::cout << "+";
          break;
        }
        ++counter;
        if (counter == answer[i].size()) {
          std::cout << "-";
        }
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string text;
  std::cin >> text;
  int dict_sz = 0;
  std::cin >> dict_sz;
  AhoCorasik aho_corasik;
  std::vector<std::string> strings(dict_sz);
  std::vector<std::pair<size_t, size_t>> ind(dict_sz);
  for (int i = 0; i < dict_sz; ++i) {
    std::cin >> ind[i].first >> ind[i].second;
    std::cin >> strings[i];
    aho_corasik.Add(strings[i], i);
  }
  aho_corasik.BuildAutomant();
  aho_corasik.GiveAnswer(text, strings, ind);
}
