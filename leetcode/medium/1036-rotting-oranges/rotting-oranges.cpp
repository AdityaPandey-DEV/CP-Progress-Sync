class Solution {
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    queue<vector<int>> q;
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
    int ans = 0;
    int fresh = 0;
    int n = grid.size();
    int m = grid[0].size();
    int minute = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 2) {
          q.push({i, j});
        } else if (grid[i][j] == 1) {
          fresh++;
        }
      }
    }
    while (!q.empty()) {
      int size = q.size();
      bool spread = false;
      for (int i = 0; i < size; i++) {
        auto v = q.front();
        q.pop();
        for (auto d : dir) {
          int nx = v[0] + d[0];
          int mx = v[1] + d[1];
          if (nx >= 0 && mx >= 0 && nx < n && mx < m && grid[nx][mx] == 1) {
            grid[nx][mx] = 2;
            q.push({nx, mx});
            spread = true;
            fresh--;
          }
        }
      }
      if (spread) {
        minute++;
      }
    }
    return (fresh == 0) ? minute : -1;
  }
};