class Solution {
  vector<int> gn = {2, 5, 6, 9};
  bool check(int n) {
    bool ans = false;
    while (n > 0) {
      int temp = n % 10;
      n /= 10;
      if (temp == 3 || temp == 4 || temp == 7) return false;
      if (find(gn.begin(), gn.end(), temp) != gn.end()) {
        ans = true;
      }
    }
    return ans;
  }

 public:
  int rotatedDigits(int n) {
    int ans = 0;
    for (int i = 0; i <= n; i++) {
      if (check(i)) {
        ans++;
      }
    }
    return ans;
  }
};