class Solution {
 public:
  vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
    int n = boxGrid.size();
    int m = boxGrid[0].size();
    vector<vector<char>> ans(m, vector<char>(n, '.'));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans[j][n - i - 1] = boxGrid[i][j];
      }
    }
    for (int j = 0; j < n; j++) {
      for (int i = m - 1; i >= 0; i--) {
        if (ans[i][j] == '.') {
          for (int k = i - 1; k >= 0; k--) {
            if (ans[k][j] == '*') {
              break;
            }
            if (ans[k][j] == '#') {
              swap(ans[i][j], ans[k][j]);
              break;
            }
          }
        }
      }
    }
    return ans;
  }
};