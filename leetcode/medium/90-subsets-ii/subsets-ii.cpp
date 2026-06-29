class Solution {
  vector<vector<int>> ans;
  void rec(vector<int> s, vector<int>& nums, int i) {
    if (i == nums.size()) {
      ans.push_back(s);
      return;
    }
    int idx = i + 1;
    while (idx < nums.size() && nums[i] == nums[idx]) {
      idx++;
    }
    rec(s, nums, idx);
    s.push_back(nums[i]);
    rec(s, nums, i + 1);
  }

 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(begin(nums), end(nums));
    vector<int> s = {};
    rec(s, nums, 0);
    return ans;
  }
};