class Solution {
 public:
  bool rotateString(string s, string goal) {
    const int size = s.size();
    s += s;
    if (size != goal.size()) return false;
    for (int i = 0; i < size; ++i) {
      int ind = 0;
      for (int j = i; j < i + size; ++j, ++ind)
        if (s[j] != goal[ind]) break;
      if (ind == size) return true;
    }
    return false;
  }
};