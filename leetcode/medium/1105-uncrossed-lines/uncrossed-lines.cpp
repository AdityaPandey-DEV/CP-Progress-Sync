class Solution {
  vector<vector<int>> dp;
  int lcs(int i, int j, vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    if (i == n1 || j == n2) {
      return 0;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    int take = 0, notTake = 0;
    if (nums1[i] == nums2[j]) {
      take = 1 + lcs(i + 1, j + 1, nums1, nums2);
    }
    notTake = max(lcs(i + 1, j, nums1, nums2), lcs(i, j + 1, nums1, nums2));
    return dp[i][j] = max(take, notTake);
  }

 public:
  int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    dp.assign(n1 + 1, vector<int>(n2 + 1, -1));
    return lcs(0, 0, nums1, nums2);
  }
};