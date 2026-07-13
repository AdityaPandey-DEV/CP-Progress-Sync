class Solution {
 public:
  vector<int> sequentialDigits(int low, int high) {
    vector<int> ans;
    queue<int> q;

    for (int i = 1; i < 9; i++) {
      q.push(i);
    }
    while (!q.empty()) {
      int d = q.front();
      q.pop();
      if (d >= low && d <= high) ans.push_back(d);
      int r = d % 10;
      r++;
      if (r == 10) continue;
      d *= 10;
      d += r;
      if (d <= high) q.push(d);
    }
    return ans;
  }
};