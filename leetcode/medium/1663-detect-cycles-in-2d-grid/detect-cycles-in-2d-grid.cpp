class Solution {
    bool dfs(int i, int j, int pi, int pj, vector<vector<char>>& grid,
             vector<vector<bool>>& vis) {
        vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int n = grid.size();
        int m = grid[0].size();

        vis[i][j] = true;
        for (auto d : dir) {
            int ni = i + d[0];
            int nj = j + d[1];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m)
                continue;
            if (grid[ni][nj] != grid[i][j])
                continue;
            if (!vis[ni][nj]) {
                if (dfs(ni, nj, i, j, grid, vis))
                    return true;
            } else if (!(ni == pi && nj == pj)) {
                return true;
            }
        }
        return false;
    }



    

public:
    bool containsCycle(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(!vis[i][j] && dfs(i,j,-1,-1,grid,vis)){
                return true;
            }
        }
    }
    return false;
   }
};