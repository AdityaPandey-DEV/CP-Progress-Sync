class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int n = nums.size();
    int l = 0;
    int r = 0;
    long long Product = 1;
    int cnt = 0;
    if (k <= 1) return 0;
    while (r < n) {
      Product *= nums[r];
      r++;
      while (Product >= k) {
        Product /= nums[l];
        l++;
      }
      cnt += (r - l);
    }
    return cnt;
  }
};