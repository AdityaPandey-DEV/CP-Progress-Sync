class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> mp;
    int n = s.size();
    int l = 0, r = 0;
    int ans = 0;
    while (r < n) {
      while (mp[s[r]] > 0) {
        mp[s[l]]--;
        l++;
      }
      mp[s[r]]++;
      r++;
      ans = max(ans, r - l);
    }
    return ans;
  }
};