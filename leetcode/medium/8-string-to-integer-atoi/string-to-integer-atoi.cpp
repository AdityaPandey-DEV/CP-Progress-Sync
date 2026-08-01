class Solution {
 public:
  int myAtoi(string s) {
    int n = s.size();
    int i = 0;

    while (i < n && s[i] == ' ') i++;

    bool positive = true;

    if (i < n && (s[i] == '+' || s[i] == '-')) {
      if (s[i] == '-') positive = false;
      i++;
    }

    long long ans = 0;

    while (i < n && isdigit(s[i])) {
      ans = ans * 10 + (s[i] - '0');

      if (positive && ans > INT_MAX) return INT_MAX;

      if (!positive && -ans < INT_MIN) return INT_MIN;

      i++;
    }

    return positive ? ans : -ans;
  }
};