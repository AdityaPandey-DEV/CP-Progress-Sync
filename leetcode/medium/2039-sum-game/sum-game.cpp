class Solution {
 public:
  bool sumGame(string num) {
    int left = 0, right = 0, leftQ = 0, rightQ = 0;
    int n = num.size();
    for (int i = 0; i < n / 2; i++) {
      if (num[i] == '?') {
        leftQ++;
      } else {
        left += num[i] - '0';
      }
    }
    for (int i = n / 2; i < n; i++) {
      if (num[i] == '?') {
        rightQ++;
      } else {
        right += num[i] - '0';
      }
    }
    if ((leftQ + rightQ) % 2 == 1) return true;
    return left - right != (rightQ - leftQ) * 9 / 2;
  }
};