class Solution {
 public:
  static bool cmp(string &a, string &b) { return a + b > b + a; }
  string largestNumber(vector<int> &nums) {
    vector<string> st;
    string ans = "";
    for (auto num : nums) {
      st.push_back(to_string(num));
    }

    sort(st.begin(), st.end(), cmp);
    for (auto s : st) {
      ans += s;
    }
    if (ans[0] == '0') return "0";
    return ans;
  }
};