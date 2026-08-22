class Solution {
  vector<int> nums;
  int n;
  int target;
  unordered_set<string> st;
  vector<int> dp;
  using ll = long long;
  bool rec(int mask, int currSum) {
    if (mask == (1 << n) - 1) {
      return true;
    }
    if (dp[mask] != -1) return dp[mask];
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) == 0) {
        if (currSum + nums[i] > target) continue;
        int nextSum = currSum + nums[i];
        int nextMask = mask | (1 << i);
        if (nextSum == target) nextSum = 0;
        if (rec(nextMask, nextSum)) return dp[mask] = true;
      }
    }
    return dp[mask] = false;
  }

 public:
  bool makesquare(vector<int>& matchsticks) {
    vector<int> side(4, 0);
    nums = matchsticks;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 4 != 0) return false;
    target = sum / 4;
    n = nums.size();
    dp.assign((1 << n), -1);
    return rec(0, 0);
  }
};