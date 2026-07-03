class Solution {
  using pii = pair<int, int>;

  int n;

  bool check(vector<vector<pii>> &adj, vector<int> &indegree,
             vector<bool> &online, int mid, long long k) {
    vector<long long> dist(n, LLONG_MAX);
    dist[0] = 0;

    queue<int> q;
    vector<int> deg = indegree;

    for (int i = 0; i < n; i++) {
      if (deg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      if (dist[u] != LLONG_MAX) {
        for (auto &[v, w] : adj[u]) {
          if (w < mid) continue;

          if (v != n - 1 && !online[v]) continue;

          if (dist[u] + w < dist[v]) dist[v] = dist[u] + w;
        }
      }

      for (auto &[v, w] : adj[u]) {
        if (--deg[v] == 0) q.push(v);
      }
    }

    return dist[n - 1] <= k;
  }

 public:
  int findMaxPathScore(vector<vector<int>> &edges, vector<bool> &online,
                       long long k) {
    n = online.size();

    vector<vector<pii>> adj(n);
    vector<int> indegree(n, 0);

    int mx = 0;

    for (auto &e : edges) {
      adj[e[0]].push_back({e[1], e[2]});
      indegree[e[1]]++;
      mx = max(mx, e[2]);
    }

    int l = 0, r = mx;
    int ans = -1;

    while (l <= r) {
      int mid = l + (r - l) / 2;

      if (check(adj, indegree, online, mid, k)) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }

    return ans;
  }
};