class Solution {
  int k, MOD = 1e9 + 7;
  vector<vector<int>> dp;
  int rec(int idx, int t) {
    if (t < 0) return 0;
    if (idx == 0) {
      if (t == 0) return 1;
      return 0;
    }
    if (dp[idx][t] != -1) return dp[idx][t];
    long long ans = 0;
    for (int i = 1; i <= k; i++) {
      ans = (ans + rec(idx - 1, t - i)) % MOD;
    }
    return dp[idx][t] = ans;
  }

 public:
  int numRollsToTarget(int n, int k, int target) {
    this->k = k;
    dp.assign(n + 1, vector<int>(target + 1, -1));
    return rec(n, target);
  }
};