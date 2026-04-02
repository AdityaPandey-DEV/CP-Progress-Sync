class Solution {
  int rec(vector<vector<int>>& coins, int i, int j, int n,
          vector<vector<vector<int>>>& dp) {
    if (i < 0 || j < 0) {
      return INT_MIN;
    }
    if (dp[i][j][n] != -1) {
      return dp[i][j][n];
    }
    if (i == 0 && j == 0) {
      if (coins[0][0] < 0 && n > 0) {
        return dp[i][j][n] = 0;
      }
      return dp[i][j][n] = coins[i][j];
    }
    int ans;
    int top = rec(coins, i - 1, j, n, dp);
    int left = rec(coins, i, j - 1, n, dp);
    int best = max(top, left);
    if (best == INT_MIN) return dp[i][j][n] = INT_MIN;
    if (coins[i][j] >= 0) {
      ans = best + coins[i][j];
    } else {
      int take = best + coins[i][j];
      int skip = INT_MIN;
      if (n > 0) {
        int topSkip = rec(coins, i - 1, j, n - 1, dp);
        int leftSkip = rec(coins, i, j - 1, n - 1, dp);
        skip = max(topSkip, leftSkip);
      }
      ans = max(take, skip);
    }
    return dp[i][j][n] = ans;
  }

 public:
  int maximumAmount(vector<vector<int>>& coins) {
    int n = coins.size();
    int m = coins[0].size();
    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(m, vector<int>(3, -1)));
    for (int k = 0; k <= 2; k++) {
      if (coins[0][0] < 0 && k > 0) {
        dp[0][0][k] = 0;
      } else {
        dp[0][0][k] = coins[0][0];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (i == 0 && j == 0) continue;
        for (int k = 0; k <= 2; k++) {
          int best = INT_MIN;
          if (i > 0) best = max(best, dp[i - 1][j][k]);
          if (j > 0) best = max(best, dp[i][j - 1][k]);
          if (best == INT_MIN) continue;
          if (coins[i][j] >= 0) {
            dp[i][j][k] = best + coins[i][j];
          } else {
            int take = best + coins[i][j];
            int skip = INT_MIN;
            if (k > 0) {
              if (i > 0) skip = max(skip, dp[i - 1][j][k - 1]);
              if (j > 0) skip = max(skip, dp[i][j - 1][k - 1]);
            }
            dp[i][j][k] = max(take, skip);
          }
        }
      }
    }
    return dp[n - 1][m - 1][2];
  }
};