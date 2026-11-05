class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    int ans = 0;
    for (auto x : arr1) {
      bool isOk = false;
      for (auto y : arr2) {
        if (abs(x - y) <= d) {
          isOk = true;
          break;
        }
      }
      if (!isOk) ans++;
    }
    return ans;
  }
};