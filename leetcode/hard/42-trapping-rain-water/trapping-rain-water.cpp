class Solution {
  vector<int> nums;
  int n;
  vector<int> maxLeft() {
    vector<int> ans(n);
    ans[0] = nums[0];
    for (int i = 1; i < n; i++) {
      ans[i] = max(ans[i - 1], nums[i]);
    }
    return ans;
  }
  vector<int> maxRight() {
    vector<int> ans(n);
    ans[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      ans[i] = max(ans[i + 1], nums[i]);
    }
    return ans;
  }

 public:
  int trap(vector<int>& height) {
    nums = height;
    n = nums.size();
    vector<int> left = maxLeft();
    vector<int> right = maxRight();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += min(right[i], left[i]) - nums[i];
    }
    return ans;
  }
};