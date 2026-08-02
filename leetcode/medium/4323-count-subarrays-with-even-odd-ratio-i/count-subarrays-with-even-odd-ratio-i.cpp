class Solution {
 public:
  int countRatioSubarrays(vector<int>& nums, int a, int b) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int x = 0, y = 0;
      for (int j = i; j < n; j++) {
        (nums[j] % 2 == 0) ? x++ : y++;
        if (y > 0 && 1ll * x * b <= 1ll * a * y) ans++;
      }
    }
    return ans;
  }
};