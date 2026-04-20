class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int sumg = accumulate(gas.begin(), gas.end(), 0);
    int sumc = accumulate(cost.begin(), cost.end(), 0);
    int sum = 0;

    int idx = 0;
    int i = idx;
    int n = gas.size();
    if (sumc > sumg)
      return -1;
    else {
      while (i < n) {
        while (sum >= 0) {
          if (i == n) break;
          sum += (gas[i] - cost[i]);
          ++i;
        }
        if (i != n) {
          sum = 0;
          idx = i;
        }
      }
      return idx;
    }
  }
};

/*
1, 2, 3, 4, 5,
3, 4, 5, 1, 2,
-2 -2 -2 3  3

*/