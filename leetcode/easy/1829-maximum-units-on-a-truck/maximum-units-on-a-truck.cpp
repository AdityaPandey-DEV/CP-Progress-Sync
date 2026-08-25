class Solution {
  static bool cmp(vector<int>& a, vector<int>& b) { return a[1] > b[1]; }

 public:
  int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    sort(boxTypes.begin(), boxTypes.end(), cmp);
    int i = 0, n = boxTypes.size();
    int ans = 0;
    while (i < n && truckSize > 0) {
      ans += min(truckSize, boxTypes[i][0]) * boxTypes[i][1];
      truckSize -= boxTypes[i][0];
      i++;
    }
    return ans;
  }
};