class Solution {
  vector<int> nums;
  int n;
  vector<vector<vector<int>>> dp;
  int rec(int p, int i, int M) {
    if (i == n) {
      return 0;
    }
    if (dp[p][i][M] != -1) return dp[p][i][M];
    int sum = 0;
    int ans = (p == 1) ? -1 : INT_MAX;
    for (int j = 0; j < min(2 * M, n - i); j++) {
      sum += nums[i + j];
      if (p == 1) {
        ans = max(ans, sum + rec(0, i + j + 1, max(M, j + 1)));
      } else {
        ans = min(ans, rec(1, i + j + 1, max(M, j + 1)));
      }
    }
    return dp[p][i][M] = ans;
  }

 public:
  int stoneGameII(vector<int>& piles) {
    nums = piles;
    n = nums.size();
    dp.assign(2, vector<vector<int>>(n, vector<int>(n + 1, -1)));
    return rec(1, 0, 1);
  }
};