class Solution {
  vector<bool> vis;
  vector<int> dept;
  int hasCycle(int u, vector<int>& edges, int i) {
    // cout<<u<<":-"<<i<<endl;
    if (u == -1) {
      return -1;
    }
    if (dept[u] != -1) {
      return i - dept[u];
    }

    if (vis[u] == true) {
      return -1;
    }
    dept[u] = i;
    vis[u] = true;
    int ans = hasCycle(edges[u], edges, i + 1);
    dept[u] = -1;
    return ans;
  }

 public:
  int longestCycle(vector<int>& edges) {
    int n = edges.size();
    vis.resize(n);
    dept.assign(n, -1);
    int ans = -1;
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        ans = max(ans, hasCycle(i, edges, 0));
      }
    }
    return ans;
  }
};