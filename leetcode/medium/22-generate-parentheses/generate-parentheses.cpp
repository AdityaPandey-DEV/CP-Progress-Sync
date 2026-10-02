class Solution {
  vector<string> ans;
  string s;
  int n;
  void rec(int i, int j) {
    if (i == n && j == n) {
      ans.push_back(s);
    }
    if (i > n) return;
    s.push_back('(');
    rec(i + 1, j);
    s.pop_back();
    if (j >= i) return;
    s.push_back(')');
    rec(i, j + 1);
    s.pop_back();
    return;
  }

 public:
  vector<string> generateParenthesis(int n) {
    this->n = n;
    rec(0, 0);
    return ans;
  }
};