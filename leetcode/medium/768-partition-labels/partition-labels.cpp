class Solution {
 public:
  vector<int> partitionLabels(string s) {
    unordered_map<char, int> mp1;
    unordered_map<char, int> mp2;
    for (auto ch : s) {
      mp1[ch]++;
    }
    vector<int> ans;
    int l = 0, r = 0;
    int n = s.size();
    int cnt = 0;

    while (r < n) {
      if (mp2.find(s[r]) == mp2.end()) {
        cnt++;
      }
      mp2[s[r]]++;
      if (mp2[s[r]] == mp1[s[r]]) {
        cnt--;
      }
      if (cnt == 0) {
        int len = r - l + 1;
        ans.push_back(len);
        l = r + 1;
      }
      r++;
    }
    return ans;
  }
};