class Solution {
    vector<bool> vis;
    vector<bool> vis1;
    vector<vector<int>> adj;
    bool ok;
    void dfs(int u) {
        vis[u] = true;
        for (auto v : adj[u]) {
            if (!vis[v]) {
                dfs(v);
            }
        }
    }
    void okDFS(int u) {
        vis1[u] = true;
        for (auto v : adj[u]) {
            if (!vis1[v]) {
                if (!vis[v]) {
                    okDFS(v);
                } else {
                    ok = true;
                    return;
                }
            }
        }
    }

public:
    vector<int> remainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {
        ok = false;
        adj.resize(n);
        for (auto i : invocations) {
            adj[i[0]].push_back(i[1]);
        }
        vis.assign(n, false);
        vis1.assign(n, false);
        dfs(k);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                okDFS(i);
            }
        }
        if (ok) {
            ans.resize(n);
            iota(ans.begin(), ans.end(), 0);
            return ans;
        }
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};