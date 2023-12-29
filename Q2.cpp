#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

class CountCyclicalShifts {
  std::string pattern_;
  std::string text_;
  std::unordered_set<size_t> hash_pattern_;
  std::vector<size_t> hash_pref_pattern_;
  std::vector<size_t> hash_pref_text_;
  std::vector<size_t> pow_p_;
  size_t p_;
  size_t result_;

 public:
  CountCyclicalShifts(const std::string&, const std::string&, const size_t& p = 2);
  size_t Result();
};

CountCyclicalShifts::CountCyclicalShifts(const std::string& pattern, const std::string& text, const size_t& p)
    : pattern_(pattern + pattern)
    , text_(text)
    , hash_pref_pattern_(pattern_.size() + 1, 0)
    , hash_pref_text_(text_.size() + 1, 0)
    , pow_p_(std::max(pattern.size(), text.size()) + 1, 1)
    , p_(p)
    , result_(0) {
  for (size_t i = 1; i < pow_p_.size(); ++i) {
    pow_p_[i] = pow_p_[i - 1] * p_;
  }
  for (size_t i = 1; i < pattern_.size() + 1; ++i) {
    hash_pref_pattern_[i] = hash_pref_pattern_[i - 1] * p_ + pattern_[i - 1];
  }
  for (size_t i = 1; i < text_.size() + 1; ++i) {
    hash_pref_text_[i] = hash_pref_text_[i - 1] * p_ + text_[i - 1];
  }
  size_t real_pat_size = pattern_.size() / 2;
  for (size_t i = 0; i < real_pat_size + 1; ++i) {
    hash_pattern_.insert(hash_pref_pattern_[i + real_pat_size] - hash_pref_pattern_[i] * pow_p_[real_pat_size]);
  }
  for (size_t i = 0, hash = 0; i + real_pat_size < text_.size() + 1; ++i) {
    hash = hash_pref_text_[i + real_pat_size] - hash_pref_text_[i] * pow_p_[real_pat_size];
    if (hash_pattern_.find(hash) != hash_pattern_.end()) {
      ++result_;
    }
  }
}

size_t CountCyclicalShifts::Result() {
  return result_;
}

int main() {
  std::string pattern;
  std::string text;
  std::cin >> pattern >> text;
  CountCyclicalShifts answer(pattern, text, 33);
  std::cout << answer.Result();
}
