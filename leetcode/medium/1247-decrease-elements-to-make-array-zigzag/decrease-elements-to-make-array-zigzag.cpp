class Solution {
 public:
  int movesToMakeZigzag(vector<int>& nums) {
    int even = 0, odd = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int left = 0, right = 0;
      if (i != 0) left = max(0, nums[i] - nums[i - 1] + 1);
      if (i != n - 1) right = max(0, nums[i] - nums[i + 1] + 1);
      int need = max(left, right);
      if (i % 2 == 0) {
        even += need;
      } else {
        odd += need;
      }
    }
    return min(even, odd);
  }
};