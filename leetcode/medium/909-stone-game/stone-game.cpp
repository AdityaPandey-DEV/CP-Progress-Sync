class Solution {
  vector<vector<int>> dp;
  vector<int> nums;
  int rec(int i, int j) {
    if (i > j) {
      return 0;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }
    int takei = nums[i] - rec(i + 1, j);
    int takej = nums[j] - rec(i, j - 1);
    return dp[i][j] = max(takei, takej);
  }

 public:
  bool stoneGame(vector<int>& piles) {
    nums = piles;
    int i = 0, j = piles.size() - 1;
    dp.assign(j + 1, vector<int>(j + 1, -1));
    return rec(i, j) >= 0;
  }
};