class Solution {
 public:
  string removeOuterParentheses(string s) {
    string ans;
    int prevI = 0, cost = 0, n = s.size();
    for (int i = 0; i < n; i++) {
      cost += (s[i] == '(') ? 1 : -1;
      // cout<<i<<" "<<cost<<endl;
      if (cost == 0) {
        // cout<<prevI<<" "<<i<<endl;
        string part = s.substr(prevI + 1, i - prevI - 1);
        ans += part;
        prevI = i + 1;
      }
    }
    return ans;
  }
};