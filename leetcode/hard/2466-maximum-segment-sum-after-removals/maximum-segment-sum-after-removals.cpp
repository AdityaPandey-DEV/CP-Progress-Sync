class DSU {
  vector<int> parent;
  vector<long long> sum;
  vector<bool> vis;
  int n;

 public:
  long long maxe = 0;
  DSU(int n) {
    this->n = n;
    parent.resize(n);
    sum.resize(n);
    vis.assign(n, false);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  int find(int u) {
    if (parent[u] == u) {
      return u;
    }
    return parent[u] = find(parent[u]);
  }
  void insert(int u, int v) {
    vis[u] = true;
    sum[u] = v;
    if (u + 1 < n && vis[u + 1]) {
      int a = find(u);
      ;
      int b = find(u + 1);
      if (a != b) {
        parent[a] = b;
        sum[b] += sum[a];
      }
    }
    if (u - 1 >= 0 && vis[u - 1]) {
      int a = find(u);
      int b = find(u - 1);
      if (a != b) {
        parent[a] = b;
        sum[b] += sum[a];
      }
    }
    maxe = max(maxe, sum[find(u)]);
  }
};

class Solution {
 public:
  vector<long long> maximumSegmentSum(vector<int>& nums,
                                      vector<int>& removeQueries) {
    int n = nums.size();
    vector<long long> ans(n);
    DSU dsu(n);
    for (int i = n - 1; i >= 0; i--) {
      ans[i] = dsu.maxe;
      dsu.insert(removeQueries[i], nums[removeQueries[i]]);
    }
    return ans;
  }
};