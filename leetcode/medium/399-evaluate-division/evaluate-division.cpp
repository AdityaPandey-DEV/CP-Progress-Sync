class Solution {
  unordered_map<string, vector<pair<string, double>>> mp;
  void dfs(string src, string dst, unordered_set<string>& vis, double prod,
           double& ans) {
    if (src == dst) {
      ans = prod;
      return;
    }
    for (auto [v, c] : mp[src]) {
      if (!vis.count(v)) {
        vis.insert(v);
        dfs(v, dst, vis, prod * c, ans);
      }
    }
  }

 public:
  vector<double> calcEquation(vector<vector<string>>& e, vector<double>& v,
                              vector<vector<string>>& q) {
    int n = e.size();
    for (int i = 0; i < n; i++) {
      mp[e[i][0]].push_back({e[i][1], v[i]});
      mp[e[i][1]].push_back({e[i][0], 1 / v[i]});
    }
    int m = q.size();
    vector<double> ans;
    for (int i = 0; i < m; i++) {
      if (mp.find(q[i][0]) == mp.end() || mp.find(q[i][1]) == mp.end()) {
        ans.push_back(-1);
        continue;
      }
      unordered_set<string> vis;
      double p = -1;
      dfs(q[i][0], q[i][1], vis, 1, p);
      ans.push_back(p);
    }
    return ans;
  }
};