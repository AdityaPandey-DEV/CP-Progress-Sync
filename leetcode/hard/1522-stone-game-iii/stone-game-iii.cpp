class Solution {
  vector<int> dp;
  int sum1, sum2;
  int n;
  vector<int> nums;
  int rec(int idx) {
    if (idx >= n) {
      return 0;
    }
    if (dp[idx] != -1) return dp[idx];
    int sum = 0;
    int maxSum = INT_MIN;
    for (int i = 0; i < 3 && i + idx < n; i++) {
      sum += nums[idx + i];
      maxSum = max(sum - rec(idx + i + 1), maxSum);
    }
    return dp[idx] = maxSum;
  }

 public:
  string stoneGameIII(vector<int>& stoneValue) {
    nums = stoneValue;
    n = nums.size();
    dp.assign(n, -1);
    int diff = rec(0);
    if (diff > 0) {
      return "Alice";
    } else if (diff < 0) {
      return "Bob";
    }
    return "Tie";
  }
};