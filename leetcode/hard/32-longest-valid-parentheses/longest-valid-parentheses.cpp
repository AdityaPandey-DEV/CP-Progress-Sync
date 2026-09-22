class Solution {
 public:
  int longestValidParentheses(string s) {
    int left = 0, right = 0, maxAns = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxAns = max(maxAns, left + right);
      } else if (right > left) {
        left = 0, right = 0;
      }
    }
    left = 0, right = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxAns = max(maxAns, left + right);
      } else if (right < left) {
        left = 0, right = 0;
      }
    }
    return maxAns;
  }
};