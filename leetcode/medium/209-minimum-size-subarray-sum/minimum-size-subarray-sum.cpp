class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int l = 0;
    int r = 0;
    int sum = 0;
    int minLen = INT_MAX;
    while (r < n) {
      sum += nums[r];
      r++;

      while (sum >= target) {
        minLen = min(abs(r - l), minLen);
        sum -= nums[l];
        l++;
      }
    }
    return (minLen == INT_MAX) ? 0 : minLen;
  }
};