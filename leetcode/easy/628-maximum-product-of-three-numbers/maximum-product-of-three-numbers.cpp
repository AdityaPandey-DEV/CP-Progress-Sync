class Solution {
 public:
  int maximumProduct(vector<int>& nums) {
    sort(rbegin(nums), rend(nums));
    int n = nums.size();
    int a = nums[0] * nums[1] * nums[2];
    int b = nums[0] * nums[n - 1] * nums[n - 2];
    return max(a, b);
  }
};