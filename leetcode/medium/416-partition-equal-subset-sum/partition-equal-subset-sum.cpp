class Solution {
  bool can(vector<int>& nums, int i, int target, vector<vector<int>>& dp) {
    if (target == 0) {
      return true;
    }
    if (target < 0) {
      return false;
    }
    int n = nums.size();
    if (i == n) {
      return false;
    }
    if (dp[i][target] != -1) {
      return (bool)dp[i][target];
    }
    int take = 0, notTake = 0;
    take = can(nums, i + 1, target - nums[i], dp);
    notTake = can(nums, i + 1, target, dp);
    return dp[i][target] = (int)(take || notTake);
  }

 public:
  bool canPartition(vector<int>& nums) {
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
    return can(nums, 0, target, dp);
  }
};