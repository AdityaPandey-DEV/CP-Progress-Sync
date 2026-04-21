class Solution {
  vector<vector<int>> dp;
  int lcs(int i, int j, vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    if (i == n1 || j == n2) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int take = 0;
    if (nums1[i] == nums2[j]) {
      return dp[i][j] = take = 1 + lcs(i + 1, j + 1, nums1, nums2);
    }
    return dp[i][j] = 0;
  }

 public:
  int findLength(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    int ans = 0;
    dp.assign(n1 + 1, vector<int>(n2 + 1, -1));
    for (int i = 0; i < n1; i++) {
      for (int j = 0; j < n2; j++) {
        if (nums1[i] == nums2[j]) {
          ans = max(ans, lcs(i, j, nums1, nums2));
        }
      }
    }
    return ans;
  }
};