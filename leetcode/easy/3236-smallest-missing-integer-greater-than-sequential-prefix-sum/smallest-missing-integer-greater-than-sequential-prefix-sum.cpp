class Solution {
 public:
  int missingInteger(vector<int>& nums) {
    int j = 1, sum = 0;
    int n = nums.size();
    sum = nums[0];
    while (j < n && nums[j] == nums[j - 1] + 1) {
      sum += nums[j];
      j++;
    }
    int ans = sum;
    cout << sum;

    sort(nums.begin(), nums.end());
    j = 0;
    while (j < n) {
      if (nums[j] < ans) {
        j++;
        continue;
      } else if (nums[j] != ans) {
        return ans;
      }
      ans++;
      j++;
    }
    return ans;
  }
};