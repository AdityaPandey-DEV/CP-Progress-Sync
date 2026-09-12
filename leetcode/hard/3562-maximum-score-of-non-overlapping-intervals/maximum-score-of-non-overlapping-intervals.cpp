class Solution {
  struct Node {
    long long score = -1;
    vector<int> idx;
  };
  int n;
  vector<vector<int>> interval;
  vector<int> nextIdx;
  vector<vector<Node>> dp;
  int findNext(int i) {
    int l = 0, r = n - 1;
    int ans = n;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (interval[mid][0] > i) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return ans;
  }
  Node solve(int i, int k) {
    if (i >= n || k == 0) return Node();
    if (dp[i][k].score != -1) return dp[i][k];
    Node skip = solve(i + 1, k);
    int weight = interval[i][2];
    int idx = interval[i][3];
    int j = nextIdx[i];
    Node temp = solve(j, k - 1);
    Node take;
    take.score = temp.score + weight;
    take.idx = temp.idx;
    take.idx.push_back(idx);
    sort(take.idx.begin(), take.idx.end());
    Node ans;
    if (skip.score > take.score) {
      ans = skip;
    } else if (skip.score < take.score) {
      ans = take;
    } else {
      ans = (skip.idx < take.idx) ? skip : take;
    }
    return dp[i][k] = ans;
  }

 public:
  vector<int> maximumWeight(vector<vector<int>>& intervals) {
    interval = intervals;
    n = interval.size();
    nextIdx.resize(n);
    for (int i = 0; i < n; i++) {
      interval[i].push_back(i);
    }
    sort(interval.begin(), interval.end());
    for (int i = 0; i < n; i++) {
      int end = interval[i][1];
      nextIdx[i] = findNext(end);
    }
    int K = 4;
    dp.assign(n + 1, vector<Node>(K + 1));
    return solve(0, K).idx;
  }
};