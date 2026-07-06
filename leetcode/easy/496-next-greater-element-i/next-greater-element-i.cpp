class Solution {
 public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int n = nums2.size();
    stack<int> s;
    unordered_map<int, int> mp;
    for (int i = n - 1; i >= 0; i--) {
      if (s.empty()) {
        mp[nums2[i]] = -1;
      }
      if (!s.empty() && s.top() > nums2[i]) {
        mp[nums2[i]] = s.top();
      } else if (!s.empty() && s.top() <= nums2[i]) {
        while (!s.empty() && s.top() <= nums2[i]) {
          s.pop();
        }
        if (s.empty()) {
          mp[nums2[i]] = -1;
        } else {
          mp[nums2[i]] = s.top();
        }
      }
      s.push(nums2[i]);
    }
    vector<int> ans(nums1.size());
    for (int i = 0; i < nums1.size(); i++) {
      ans[i] = mp[nums1[i]];
    }
    return ans;
  }
};