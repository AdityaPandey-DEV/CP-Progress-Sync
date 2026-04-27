class Solution {
  unordered_map<int, vector<pair<int, int>>> mp = {
      {1, {{0, 1}, {0, -1}}}, {2, {{1, 0}, {-1, 0}}},  {3, {{0, -1}, {1, 0}}},
      {4, {{0, 1}, {1, 0}}},  {5, {{0, -1}, {-1, 0}}}, {6, {{0, 1}, {-1, 0}}}};

  bool dfs(int i, int j, int pi, int pj, vector<vector<int>>& grid,
           vector<vector<bool>>& vis) {
    int n = grid.size();
    int m = grid[0].size();
    if (i < 0 || j < 0 || i == n || j == m) {
      return false;
    }
    if (vis[i][j]) return false;
    vis[i][j] = true;
    if (i == n - 1 && j == m - 1) {
      return true;
    }

    auto dir = mp[grid[i][j]];
    for (auto& p : dir) {
      int ni = p.first + i;
      int nj = p.second + j;
      if (ni == pi && nj == pj) {
        continue;
      }
      if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
      bool valid = false;

      for (auto& back : mp[grid[ni][nj]]) {
        if (ni + back.first == i && nj + back.second == j) {
          valid = true;
          break;
        }
      }
      if (valid && dfs(ni, nj, i, j, grid, vis)) {
        return true;
      }
    }
    return false;
  }

 public:
  bool hasValidPath(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    return dfs(0, 0, -1, -1, grid, vis);
  }
};