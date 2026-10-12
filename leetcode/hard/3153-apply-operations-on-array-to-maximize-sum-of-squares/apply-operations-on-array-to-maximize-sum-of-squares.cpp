class Solution {
 public:
  int maxSum(vector<int>& nums, int k) {
    int MOD = 1e9 + 7;
    long long ans = 0;
    vector<int> cnt(32, 0);
    for (auto num : nums) {
      for (int i = 0; i < 32; i++) {
        if (num & (1 << i)) {
          cnt[i]++;
        }
      }
    }
    while (k--) {
      long long cur = 0;
      for (int i = 0; i < 32; i++) {
        if (cnt[i] > 0) {
          cnt[i]--;
          cur |= (1 << i);
        }
      }
      ans = (ans + (cur * cur)) % MOD;
    }
    return ans;
  }
};