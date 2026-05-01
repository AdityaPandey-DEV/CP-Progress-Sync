class Solution {
  vector<vector<string>> ans;
  bool isPal(int i, int j, string s) {
    if (i >= j) return true;
    if (s[i] == s[j]) {
      return isPal(i + 1, j - 1, s);
    } else {
      return false;
    }
  }
  void solve(int idx, string &s, vector<string> path) {
    if (idx == s.size()) {
      ans.push_back(path);
    }
    for (int j = idx; j < s.size(); j++) {
      if (isPal(idx, j, s)) {
        path.push_back(s.substr(idx, j - idx + 1));
        solve(j + 1, s, path);
        path.pop_back();
      }
    }
  }

 public:
  vector<vector<string>> partition(string s) {
    vector<string> path;
    solve(0, s, path);
    return ans;
  }
};