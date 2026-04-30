class Solution {
  vector<vector<int>> ans;
  unordered_set<int> st;
  void func(vector<int>& temp, vector<int>& nums) {
    int n = nums.size();
    if (temp.size() == n) {
      ans.push_back(temp);
      return;
    }
    for (int i = 0; i < n; i++) {
      if (st.find(nums[i]) == st.end()) {
        st.insert(nums[i]);
        temp.push_back(nums[i]);
        func(temp, nums);
        st.erase(nums[i]);
        temp.pop_back();
      }
    }
  }

 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<int> temp;
    func(temp, nums);
    return ans;
  }
};