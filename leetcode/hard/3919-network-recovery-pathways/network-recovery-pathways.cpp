class Solution {
  using ppi = pair<int, int>;
  using pll = pair<long long, int>;
  using ll = long long;

  int n;
  bool check(int mid, ll k, unordered_map<int, vector<vector<int>>>& al) {
    vector<ll> ans(n, LLONG_MAX);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    ans[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
      ll d = pq.top().first;
      int node = pq.top().second;
      pq.pop();
      if (d > k) {
        return false;
      }
      if (node == n - 1) {
        return true;
      }
      if (ans[node] < d) continue;
      for (auto e : al[node]) {
        int v = e[0];
        int c = e[1];
        if (c < mid) continue;
        if (d + c < ans[v]) {
          ans[v] = d + c;
          pq.push({d + c, v});
        }
      }
    }
    return false;
  }

 public:
  int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online,
                       long long k) {
    n = online.size();
    unordered_map<int, vector<vector<int>>> al;
    int l = 1e9, r = 0;
    for (auto& e : edges) {
      int u = e[0];
      int v = e[1];
      int c = e[2];
      if (!online[u] || !online[v]) continue;
      al[u].push_back({v, c});
      r = max(r, c);
      l = min(l, c);
    }

    int ans = -1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (check(mid, k, al)) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return ans;
  }
};