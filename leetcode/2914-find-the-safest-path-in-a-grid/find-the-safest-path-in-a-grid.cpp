class Solution {
    using ppi = pair<int, int>;
    
    bool check(vector<vector<int>>& dis, int mid) {
        vector<vector<int>> dir({{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
        queue<ppi> q;
        int n = dis.size();
        if(dis[0][0] < mid) return false;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        q.push({0, 0});
        vis[0][0] = true;
        while (!q.empty()) {
            ppi p = q.front();
            q.pop();
            if (p.first == n - 1 && p.second == n - 1) {
                return true;
            }
            for (vector<int>& d : dir) {
                int i = p.first + d[0];
                int j = p.second + d[1];
                if (i < 0 || i >= n || j < 0 || j >= n || vis[i][j]||dis[i][j]<mid) {
                    
                    continue;
                }
                q.push({i, j});
                vis[i][j] = true;
            }
        }
        return false;
    }

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        vector<vector<int>> dir({{1, 0}, {-1, 0}, {0, 1}, {0, -1}});

        int n = grid.size();

        vector<vector<int>> dis(n, vector<int>(n, -1));
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        queue<ppi> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = true;
                }
            }
        }
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                ppi p = q.front();
                q.pop();
                dis[p.first][p.second] = level;
                for (vector<int>& d : dir) {
                    int i = p.first + d[0];
                    int j = p.second + d[1];
                    if (i < 0 || i >= n || j < 0 || j >= n || vis[i][j]) {
                        continue;
                    }
                    q.push({i, j});
                    vis[i][j] = true;
                }
            }
            level++;
        }
        int l = 0, r = 400;
        int ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(dis, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};