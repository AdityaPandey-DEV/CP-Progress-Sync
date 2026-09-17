class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int canreach = 0;
    int i, n = nums.size();
    if (n == 1) return true;
    for (i = 0; i < n - 1; i++) {
      if (canreach < i) break;
      canreach = max(nums[i] + i, canreach);
      // cout<<i<<endl;
    }
    cout << i << endl;
    return canreach >= n - 1;
  }
};