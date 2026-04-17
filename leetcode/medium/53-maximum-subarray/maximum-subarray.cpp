class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int n = nums.size();
    int sum = nums[0];
    for (int i = 1; i < n; i++) {
      sum = max(nums[i], sum + nums[i]);
      maxSum = max(sum, maxSum);
    }
    return maxSum;
  }
};