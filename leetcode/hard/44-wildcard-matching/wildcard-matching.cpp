class Solution {
  string s, p;
  int n, m;
  vector<vector<int>> dp;
  bool rec(int i, int j) {
    if (i == s.size() && j == p.size()) {
      return true;
    }
    if (i == s.size() + 1 || j == p.size() + 1) {
      return false;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }
    bool ans = false;
    if (s[i] == p[j] || p[j] == '?') {
      ans |= rec(i + 1, j + 1);
    }
    if (p[j] == '*') {
      ans |= rec(i, j + 1) || rec(i + 1, j);
    }
    return dp[i][j] = ans;
  }

 public:
  bool isMatch(string s, string p) {
    this->s = s;
    this->p = p;
    n = s.size();
    m = p.size();
    dp.assign(n + 2, vector<int>(m + 2, -1));
    return rec(0, 0);
  }
};