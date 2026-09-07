class Solution {
  int n, m;
  string s, t;
  vector<vector<long long>> dp;
  int rec(int i, int j) {
    if (j == m) return 1;
    if (i == n) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    long long notTake = rec(i + 1, j);
    long long take = rec(i + 1, j + 1);
    if (s[i] == t[j]) {
      return dp[i][j] = take + notTake;
    }
    return dp[i][j] = notTake;
  }

 public:
  int numDistinct(string s, string t) {
    this->s = s;
    this->t = t;
    n = s.size(), m = t.size();
    dp.assign(n, vector<long long>(m, -1));
    return rec(0, 0);
  }
};