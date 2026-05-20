class Solution {
 public:
  vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
    int n = A.size();
    set<int> s;
    vector<int> ans(n, 0);
    int c = 0;
    for (int i = 0; i < n; i++) {
      if (s.count(A[i]) == 1) {
        c++;
      }
      s.insert(A[i]);
      if (s.count(B[i]) == 1) {
        c++;
      }

      s.insert(B[i]);
      ans[i] = c;
    }
    return ans;
  }
};