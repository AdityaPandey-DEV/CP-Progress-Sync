class Solution {
  vector<vector<int>> dp;
  int rec(int i, int j) {
    if (i >= j) {
      return 0;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }
    int ans = 1e9;
    for (int k = i; k < j; k++) {
      int total = k + max(rec(i, k - 1), rec(k + 1, j));
      ans = min(ans, total);
    }
    return dp[i][j] = ans;
  }

 public:
  int getMoneyAmount(int n) {
    dp.assign(n + 1, vector<int>(n + 1, -1));
    return rec(0, n);
  }
};