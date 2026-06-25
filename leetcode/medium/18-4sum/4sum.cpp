class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(begin(nums), end(nums));
    int n = nums.size();
    vector<vector<int>> ans;
    for (int a = 0; a < n; a++) {
      if (a > 0 && nums[a] == nums[a - 1]) continue;
      for (int b = a + 1; b < n;) {
        int c = b + 1, d = n - 1;
        while (c < d) {
          long long sum = 1LL * nums[a] + nums[b] + nums[c] + nums[d];
          if (sum < target) {
            c++;
          } else if (sum > target) {
            d--;
          } else {
            ans.push_back({nums[a], nums[b], nums[c], nums[d]});
            c++;
            d--;
            while (c < d && nums[c] == nums[c - 1]) c++;
            while (c < d && nums[d] == nums[d + 1]) d--;
          }
        }
        b++;
        while (b < n && nums[b] == nums[b - 1]) b++;
      }
    }
    return ans;
  }
};