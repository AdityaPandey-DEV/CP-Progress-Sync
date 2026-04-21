class DSU {
  vector<int> parent;
  vector<int> size;

 public:
  DSU(int n) {
    size.assign(n, 1);
    parent.assign(n, 1);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  int find(int i) {
    if (i == parent[i]) {
      return i;
    }
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    i = find(i);
    j = find(j);
    if (i != j) {
      if (size[i] < size[j]) {
        swap(i, j);
      }
      parent[j] = i;
      size[i] += size[j];
    }
  }
};
class Solution {
 public:
  int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    int m = isConnected[0].size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (isConnected[i][j] == 1) {
          dsu.unite(i, j);
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (dsu.find(i) == i) {
        ans++;
      }
    }
    return ans;
  }
};