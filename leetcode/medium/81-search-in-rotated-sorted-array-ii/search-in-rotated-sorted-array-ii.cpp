class Solution {
 public:
  bool search(vector<int>& nums, int t) {
    int n = nums.size();
    int st = 0, end = n - 1, mid;
    while (st <= end) {
      mid = st + (end - st) / 2;
      if (nums[mid] == t) return 1;
      if (nums[st] == nums[mid] && nums[mid] == nums[end]) {
        st++, end--;
        continue;
      }
      if (nums[st] <= nums[mid]) {
        if (nums[mid] > t && nums[st] <= t) {
          end = mid - 1;
        } else {
          st = mid + 1;
        }
      } else {
        if (nums[mid] < t && t <= nums[end]) {
          st = mid + 1;
        } else {
          end = mid - 1;
        }
      }
    }
    return 0;
  }
};