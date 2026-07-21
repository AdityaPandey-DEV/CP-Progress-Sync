class Solution {
 public:
  int maxActiveSectionsAfterTrade(string s) {
    int n = s.size();
    vector<int> block;
    int sum = 0;
    int one = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        one++;
        if (sum > 0) {
          block.push_back(sum);
          sum = 0;
        }
      } else {
        sum++;
      }
    }
    if (sum > 0) {
      block.push_back(sum);
    }
    int ans = 0;
    int m = block.size();
    for (int i = 1; i < m; i++) {
      int sum = block[i - 1] + block[i];
      ans = max(sum, ans);
    }
    return ans + one;
  }
};