class Solution {
  using ll = long long;
  int MOD = 1e9 + 7;

 public:
  int valueAfterKSeconds(int n, int k) {
    vector<ll> nums(n, 1);
    for (int i = 0; i < k; i++) {
      for (int j = 1; j < n; j++) {
        nums[j] = (nums[j] + nums[j - 1]) % MOD;
      }
    }
    return nums[n - 1];
  }
};