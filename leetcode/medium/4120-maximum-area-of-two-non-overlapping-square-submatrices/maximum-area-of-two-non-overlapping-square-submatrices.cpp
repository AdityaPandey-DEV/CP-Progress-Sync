class Solution {
  int n, m;
  int INF = 1e9;
  vector<vector<int>> pref;
  bool check(int k) {
    int minRow = INF, maxRow = -INF;
    int minCol = INF, maxCol = -INF;
    for (int i = 0; i <= n - k; i++) {
      for (int j = 0; j <= m - k; j++) {
        int sum =
            pref[i + k][j + k] - pref[i][j + k] - pref[i + k][j] + pref[i][j];
        if (sum == k * k) {
          minRow = min(minRow, i);
          maxRow = max(maxRow, i);
          minCol = min(minCol, j);
          maxCol = max(maxCol, j);
        }
      }
    }
    return (maxRow - minRow >= k) || (maxCol - minCol >= k);
  }

 public:
  int maxArea(vector<vector<int>>& mat) {
    n = mat.size();
    m = mat[0].size();
    int l = 0, r = min(n, m);
    pref.assign(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        pref[i + 1][j + 1] =
            pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + mat[i][j];
      }
    }
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (check(mid)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return r * r;
  }
};