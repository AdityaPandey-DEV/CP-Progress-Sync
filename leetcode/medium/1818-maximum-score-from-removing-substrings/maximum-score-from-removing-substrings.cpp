class Solution {
  int remove(string &s, char start, char end, int score) {
    string st;
    int ans = 0;
    for (auto ch : s) {
      if (!st.empty() && st.back() == start && ch == end) {
        st.pop_back();
        ans += score;
      } else {
        st.push_back(ch);
      }
    }
    s = st;
    return ans;
  }

 public:
  int maximumGain(string s, int x, int y) {
    int ans = 0;
    if (x > y) {
      ans += remove(s, 'a', 'b', x);
      ans += remove(s, 'b', 'a', y);
    } else {
      ans += remove(s, 'b', 'a', y);
      ans += remove(s, 'a', 'b', x);
    }
    return ans;
  }
};