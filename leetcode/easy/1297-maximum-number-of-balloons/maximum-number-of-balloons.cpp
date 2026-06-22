class Solution {
 public:
  int maxNumberOfBalloons(string text) {
    unordered_map<char, int> freq;
    for (auto c : text) {
      freq[c]++;
    }
    string b = "balloon";
    int ans = 1e9;
    for (auto c : b) {
      int count = freq[c];
      if (c == 'l' || c == 'o') {
        count /= 2;
      }
      ans = min(count, ans);
    }
    return (ans == 1e9 || ans < 0) ? 0 : ans;
  }
};