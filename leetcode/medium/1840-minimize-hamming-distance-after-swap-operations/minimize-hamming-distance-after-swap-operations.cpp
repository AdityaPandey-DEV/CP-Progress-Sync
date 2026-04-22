class Solution {
  class DSU {
    vector<int> parent;
    vector<int> size;

   public:
    DSU(int n) {
      parent.assign(n, 0);
      size.assign(n, 1);
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

 public:
  int minimumHammingDistance(vector<int>& source, vector<int>& target,
                             vector<vector<int>>& allowedSwaps) {
    const int size = source.size();
    DSU dsu(size);
    int result = 0;
    for (const vector<int>& i : allowedSwaps) {
      int a = i[0], b = i[1];
      dsu.unite(a, b);
    }
    unordered_map<int, unordered_map<int, int>> hash;
    for (int i = 0; i < size; ++i) {
      int parent = dsu.find(i);
      ++hash[parent][source[i]];
      ++result;
    }
    for (int i = 0; i < size; ++i) {
      int parent = dsu.find(i);
      if (hash.count(parent) && hash[parent].count(target[i])) {
        --hash[parent][target[i]];
        --result;
        if (hash[parent][target[i]] == 0) hash[parent].erase(target[i]);
      }
    }
    return result;
  }
};