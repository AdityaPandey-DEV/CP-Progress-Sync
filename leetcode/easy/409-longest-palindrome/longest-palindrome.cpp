class Solution {
 public:
  int longestPalindrome(string s) {
    int ans = 0;

    unordered_map<char, int> mp;
    for (auto ch : s) {
      mp[ch]++;
    }
    int one = 0;
    for (auto it : mp) {
      int i = it.second;
      if (i % 2 == 0) {
        ans += i;
      } else if (i % 2 == 1) {
        ans += i - 1;
        one = 1;
      }
    }
    return ans + one;
  }
};