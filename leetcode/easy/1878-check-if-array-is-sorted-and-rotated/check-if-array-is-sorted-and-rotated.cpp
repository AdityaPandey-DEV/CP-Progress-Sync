class Solution {
 public:
  bool check(vector<int>& nums) {
    vector<int> temp = nums;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int a;
    for (int j = 0; j < n; j++) {
      a = nums[0];
      for (int i = 0; i < n - 1; i++) {
        int b = nums[i + 1];
        nums[i + 1] = a;
        a = b;
      }
      nums[0] = a;
      if (nums == temp) {
        return true;
      }
    }

    return false;
  }
};