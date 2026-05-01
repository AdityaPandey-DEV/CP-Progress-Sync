class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> q;
    vector<int> ans;
    int l = 0, r = 0;
    int n = nums.size();
    while (r < n) {
      while (!q.empty() && nums[q.back()] < nums[r]) {
        q.pop_back();
      }
      q.push_back(r);
      if (!q.empty() && q.front() < l) {
        q.pop_front();
      }
      if (r - l + 1 == k) {
        ans.push_back(nums[q.front()]);
        l++;
      }
      r++;
    }
    return ans;
  }
};