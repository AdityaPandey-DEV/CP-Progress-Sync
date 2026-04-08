class Solution {
 public:
  int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
    const int mod = 1e9 + 7;
    for (auto q : queries) {
      int l = q[0];
      int v = q[3];
      int r = q[1];
      int k = q[2];
      if (k == 0) continue;
      for (int i = l; i <= r; i += k) {
        nums[i] = (1LL * nums[i] * v) % mod;
      }
    }
    int ans = 0;
    for (int i = 0; i < nums.size(); i++) {
      ans ^= nums[i];
    }
    return ans;
  }
};