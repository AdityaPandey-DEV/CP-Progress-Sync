class Solution {
  vector<int> pref;
  vector<int> nums;
  int n;
  vector<int> dp;
  int rec(int idx) {
    if (idx == n - 1) return pref[idx];
    if (dp[idx] != INT_MIN) return dp[idx];
    int next = rec(idx + 1);
    return dp[idx] = max(pref[idx] - next, next);
  }

 public:
  int stoneGameVIII(vector<int>& stones) {
    n = stones.size();
    pref.assign(n, 0);
    pref[0] = stones[0];
    for (int i = 0; i < n; i++) {
      if (i != 0) pref[i] = pref[i - 1] + stones[i];
      // cout<<pref[i]<<"  ";
    }
    nums = stones;
    dp.assign(n, INT_MIN);
    // cout<<ans<<endl;
    return rec(1);
  }
};