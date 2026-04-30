class Solution {
 public:
  string removeKdigits(string num, int k) {
    string ans;
    int n = num.size();
    ans.push_back(num[0]);
    for (int i = 1; i < n; i++) {
      while (!ans.empty() && ans.back() > num[i] && k > 0) {
        k--;
        ans.pop_back();
      }
      ans.push_back(num[i]);
    }
    while (!ans.empty() && k > 0) {
      k--;
      ans.pop_back();
    }
    int i = 0;
    while (i < ans.size() && ans[i] == '0') {
      i++;
    }
    ans = ans.substr(i);
    return (ans == "") ? "0" : ans;
  }
};