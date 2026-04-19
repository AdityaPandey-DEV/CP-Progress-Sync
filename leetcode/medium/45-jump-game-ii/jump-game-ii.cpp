class Solution {
 public:
  int jump(vector<int>& nums) {
    int n = nums.size();
    int f = nums[0];
    int cnt = 0;
    int m = 0;
    int maxr = 0;
    int end = 0;
    for (int i = 0; i < n - 1; i++) {
      maxr = max(maxr, i + nums[i]);
      if (i == end) {
        cnt++;
        end = maxr;
      }
    }
    return cnt;
  }
};