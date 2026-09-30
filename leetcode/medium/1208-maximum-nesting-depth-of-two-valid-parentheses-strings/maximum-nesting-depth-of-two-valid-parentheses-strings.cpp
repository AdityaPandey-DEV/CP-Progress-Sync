class Solution {
 public:
  vector<int> maxDepthAfterSplit(string seq) {
    vector<int> ans;
    int dept = 0;
    int n = seq.size();
    ans.assign(n, -1);
    for (int i = 0; i < n; i++) {
      if (seq[i] == '(') {
        dept++;
      }
      if (dept % 2 == 0) {
        ans[i] = 1;
      } else {
        ans[i] = 0;
      }
      if (seq[i] == ')') {
        dept++;
      }
    }
    return ans;
  }
};