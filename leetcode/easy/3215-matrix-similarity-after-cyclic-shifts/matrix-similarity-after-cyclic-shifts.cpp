class Solution {
 public:
  bool areSimilar(vector<vector<int>>& mat, int k) {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> ma(n, vector<int>(m));
    k %= m;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        for (int j = 0; j < m; j++) {
          int ni = (j - k + m) % m;
          ma[i][ni] = mat[i][j];
        }
      } else {
        for (int j = 0; j < m; j++) {
          int ni = (j + k) % m;
          ma[i][ni] = mat[i][j];
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mat[i][j] != ma[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
};