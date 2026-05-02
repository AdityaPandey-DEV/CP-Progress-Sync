class DSU {
  vector<int> parent;
  vector<int> size;

 public:
  DSU(int n) {
    size.assign(n, 1);
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int n) {
    if (parent[n] == n) {
      return n;
    }
    return parent[n] = find(parent[n]);
  }
  void unite(int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j) return;
    if (size[i] > size[j]) {
      swap(i, j);
    }
    size[j] += size[i];
    parent[i] = j;
  }
};

class Solution {
 public:
  int makeConnected(int n, vector<vector<int>>& connections) {
    if (connections.size() < n - 1) {
      return -1;
    }
    DSU dsu(n);
    for (auto& edge : connections) {
      int i = edge[0];
      int j = edge[1];
      dsu.unite(i, j);
    }
    int p = dsu.find(0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (dsu.find(i) == i) {
        ans++;
      }
    }
    return ans - 1;
  }
};