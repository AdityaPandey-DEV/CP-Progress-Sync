class Solution {
  using ll = long long;

 public:
  long long countCommas(long long n) {
    ll totalCnt = 0, cnt = 1;
    if (n < 1000) return 0;
    ll i = 1000;
    while (n >= i) {
      ll ni = i * 1000 - 1;
      if (ni > n) ni = n;
      totalCnt += ((ni - i + 1) * cnt);
      cnt++;
      i *= 1000;
    }
    return totalCnt;
  }
};