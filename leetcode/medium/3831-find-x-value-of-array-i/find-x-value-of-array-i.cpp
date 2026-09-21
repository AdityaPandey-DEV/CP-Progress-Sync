class Solution {
 public:
  vector<long long> resultArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> ans(k, 0);
    vector<long long> prev(k, 0);
    for (int i = 0; i < n; i++) {
      vector<long long> curr(k, 0);
      int currElement = nums[i] % k;
      curr[currElement]++;
      for (int old = 0; old < k; old++) {
        int newI = ((long long)old * (nums[i] % k)) % k;
        curr[newI] += prev[old];
      }
      prev = std::move(curr);
      for (int j = 0; j < k; j++) {
        ans[j] += prev[j];
      }
    }
    return ans;
  }
};