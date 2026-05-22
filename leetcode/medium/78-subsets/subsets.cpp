class Solution {
 public:
  void getAllSubsets(vector<int>& ans, vector<vector<int>>& allsubsets, int i,
                     vector<int>& nums, int& n) {
    if (n == i) {
      allsubsets.push_back({ans});
      return;
    }
    // insert
    ans.push_back(nums[i]);
    getAllSubsets(ans, allsubsets, i + 1, nums, n);
    // exclude
    ans.pop_back();
    getAllSubsets(ans, allsubsets, i + 1, nums, n);
  }
  vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
    vector<vector<int>> allsubsets;
    getAllSubsets(ans, allsubsets, 0, nums, n);
    return allsubsets;
  }
};
