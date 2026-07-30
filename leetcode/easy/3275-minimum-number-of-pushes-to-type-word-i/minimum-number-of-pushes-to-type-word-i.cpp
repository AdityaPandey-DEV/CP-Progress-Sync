class Solution {
 public:
  int minimumPushes(string word) {
    int ans = 0;
    int n = word.size();
    int i = 1;
    while (n) {
      if (n < 8) {
        ans += n * i;
        break;
      }
      n -= 8;
      ans += (8 * i);
      cout << ans;
      i++;
    }
    return ans;
  }
};