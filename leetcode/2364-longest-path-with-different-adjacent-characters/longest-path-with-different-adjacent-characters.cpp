class Solution {
    vector<vector<int>> adj;
    string s;
    int ans;
    int dfs(int u) {
        if (adj[u].size() == 0) {
            return 1;
        }
        int ans1 = 0, ans2 = 0;
        for (auto& v : adj[u]) {
            int a = dfs(v);
            if(s[u]==s[v])continue;
            cout << endl;
        
            if (a != 0) {
                if (a > ans1) {
                    ans2 = ans1;
                    ans1 = a;
                } else if (a > ans2) {
                    ans2 = a;
                }
            }
        }
        
        ans = max(ans, 1 + ans1 + ans2);
        return 1 + ans1;
        
        
    }

public:
    int longestPath(vector<int>& parent, string s) {
        this->s = s;
        int n = parent.size();
        adj.resize(n);
        ans = 0;
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }
        return max(ans, dfs(0));
    }
};