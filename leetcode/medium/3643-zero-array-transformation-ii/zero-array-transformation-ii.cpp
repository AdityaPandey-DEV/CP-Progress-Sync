class Solution {
  bool isValid(vector<int>& nums, vector<vector<int>>& q, int k) {
    int n = nums.size();
    vector<int> diff(n);
    for (int i = 0; i < k; i++) {
      int l = q[i][0];
      int r = q[i][1];
      int v = q[i][2];
      diff[l] += v;
      if (r + 1 < n) diff[r + 1] -= v;
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += diff[i];
      if (sum < nums[i]) {
        return false;
      }
    }
    return true;
  }

 public:
  int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = queries.size();
    int l = 0, r = n;
    int ans = -1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (isValid(nums, queries, mid)) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return ans;
  }
};