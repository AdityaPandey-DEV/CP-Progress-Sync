class Solution {
  vector<vector<int>> dp;
  int lcs(int i, int j, string &s1, string &s2) {
    int n1 = s1.size(), n2 = s2.size();
    if (j == s2.size()) return 1;
    if (i == s1.size()) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int take = 0, notTake = 0;
    if (s1[i] == s2[j]) {
      take = lcs(i + 1, j + 1, s1, s2);
    }
    notTake = lcs(i + 1, j, s1, s2);
    return dp[i][j] = take + notTake;
  }

 public:
  int numDistinct(string s, string t) {
    int n = s.size();
    int m = t.size();
    dp.assign(n + 1, vector<int>(m + 1, -1));
    int ans = lcs(0, 0, s, t);
    return ans;
  }
};