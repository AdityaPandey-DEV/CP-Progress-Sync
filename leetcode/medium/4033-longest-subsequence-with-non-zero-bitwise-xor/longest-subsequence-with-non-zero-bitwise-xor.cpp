class Solution {
 public:
  int longestSubsequence(vector<int>& nums) {
    int x = 0;
    bool allZero = true;
    int n = nums.size();
    for (int i : nums) {
      x ^= i;
      if (i != 0) allZero = false;
    }
    if (allZero) return 0;
    if (x != 0) return n;
    return n - 1;
  }
};