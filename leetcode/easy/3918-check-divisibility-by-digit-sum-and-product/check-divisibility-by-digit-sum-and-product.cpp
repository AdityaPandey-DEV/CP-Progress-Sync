class Solution {
 public:
  bool checkDivisibility(int n) {
    int sum = 0, product = 1;
    int m = n;
    while (m) {
      int r = m % 10;
      m /= 10;
      sum += r;
      product *= r;
    }
    sum += product;

    return n % sum == 0;
  }
};