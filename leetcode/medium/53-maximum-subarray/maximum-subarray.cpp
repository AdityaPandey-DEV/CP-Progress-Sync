class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    int maxSum = -1e9;
    int sum = -1e9;
    for (int i = 0; i < n; i++) {
      sum = max(sum + nums[i], nums[i]);
      maxSum = max(sum, maxSum);
    }
    return maxSum;
  }
};