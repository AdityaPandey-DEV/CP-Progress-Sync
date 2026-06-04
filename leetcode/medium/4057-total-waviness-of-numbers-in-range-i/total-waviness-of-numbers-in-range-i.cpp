class Solution {
  int getAns(int n) {
    string s = to_string(n);
    int ans = 0;
    for (int i = 1; i < s.size() - 1; i++) {
      if (s[i - 1] > s[i] && s[i + 1] > s[i]) {
        ans++;
      }
      if (s[i - 1] < s[i] && s[i + 1] < s[i]) {
        ans++;
      }
    }
    return ans;
  }

 public:
  int totalWaviness(int num1, int num2) {
    int ans = 0;
    for (int n = num1; n <= num2; n++) {
      ans += getAns(n);
    }
    return ans;
  }
};