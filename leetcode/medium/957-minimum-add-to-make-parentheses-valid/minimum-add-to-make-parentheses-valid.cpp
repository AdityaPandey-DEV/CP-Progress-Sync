class Solution {
 public:
  int minAddToMakeValid(string s) {
    int ans = 0, cnt = 0, n = s.size();
    for (int i = 0; i < n; i++) {
      cnt += (s[i] == '(') ? 1 : -1;
      if (cnt < 0) {
        ans += abs(cnt);
        cnt = 0;
      }
    }
    return ans + abs(cnt);
  }
};