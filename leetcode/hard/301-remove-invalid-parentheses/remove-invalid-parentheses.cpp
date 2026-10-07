class Solution {
  unordered_set<string> st;
  int maxLen = 0;
  string s;
  int n;
  void getStr(int i, int &cost, string &ans) {
    // cout<<i<<" "<<cost<<" "<<ans<<endl;
    if (i == n && cost == 0) {
      int size = ans.size();
      if (size == maxLen) {
        st.insert(ans);
      }
      if (size > maxLen) {
        maxLen = size;
        st.clear();
        st.insert(ans);
      }
      return;
    }
    if (cost < 0 || i > n) return;
    if (isalpha(s[i])) {
      ans.push_back(s[i]);
      getStr(i + 1, cost, ans);
      ans.pop_back();
      return;
    }
    int c = (s[i] == '(') ? 1 : -1;
    ans.push_back(s[i]);
    cost += c;
    getStr(i + 1, cost, ans);
    ans.pop_back();
    cost -= c;
    getStr(i + 1, cost, ans);
  }

 public:
  vector<string> removeInvalidParentheses(string s) {
    this->s = s;
    n = s.size();
    string a = "";
    int cost = 0;
    getStr(0, cost, a);
    vector<string> ans(st.begin(), st.end());
    return ans;
  }
};