class Solution {
  const int NEG = -1e9;

  int rec(int i, int j, vector<vector<int>>& grid, int k,
          vector<vector<vector<int>>>& dp) {
    int n = grid.size();
    int m = grid[0].size();

    if (i >= n || j >= m) return NEG;

    int cost = (grid[i][j] == 0 ? 0 : 1);

    if (k < cost) return NEG;

    if (i == n - 1 && j == m - 1) {
      return grid[i][j];
    }

    if (dp[i][j][k] != -1) {
      return dp[i][j][k];
    }

    int r = rec(i, j + 1, grid, k - cost, dp);
    int d = rec(i + 1, j, grid, k - cost, dp);

    int best = max(r, d);

    if (best == NEG) {
      return dp[i][j][k] = NEG;
    }

    return dp[i][j][k] = grid[i][j] + best;
  }

 public:
  int maxPathScore(vector<vector<int>>& grid, int k) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(
        n, vector<vector<int>>(m, vector<int>(k + 1, -1)));
    int ans = rec(0, 0, grid, k, dp);
    return (ans < 0) ? -1 : ans;
  }
};