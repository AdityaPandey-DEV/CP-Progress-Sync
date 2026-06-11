class Solution {
  int dfs(unordered_map<int, vector<int>>& al, unordered_map<int, bool>& vis,
          int curr) {
    vis[curr] = true;

    int dept = 1;
    int maxdept = 1;
    for (auto l : al[curr]) {
      if (!vis[l]) {
        dept = 1 + dfs(al, vis, l);
        maxdept = max(maxdept, dept);
      }
    }

    return maxdept;
  }
  long long power(long long a, long long b) {
    long long mod = 1e9 + 7;
    long long res = 1;
    while (b) {
      if (b & 1) res = (res * a) % mod;
      a = (a * a) % mod;
      b >>= 1;
    }
    return res;
  }

 public:
  int assignEdgeWeights(vector<vector<int>>& edges) {
    int n = edges.size() + 1;

    unordered_map<int, vector<int>> al(n);
    for (auto& edge : edges) {
      int a = edge[0];
      int b = edge[1];
      al[a].push_back(b);
      al[b].push_back(a);
    }

    unordered_map<int, bool> vis;
    int mdept = dfs(al, vis, 1);
    long long ans = power(2, mdept - 2);
    return ans;
  }
};