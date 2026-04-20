class Solution {
 public:
  int longestOnes(vector<int>& nums, int k) {
    int zero = 0;
    int l = 0, r = 0;
    int dis = 0;
    int n = nums.size();
    while (r < n && l < n) {
      if (nums[r] == 0) zero++;
      while (zero > k) {
        if (nums[l] == 0) {
          zero--;
        }
        l++;
      }

      r++;
      dis = max(dis, r - l);
    }
    return dis;
  }
};