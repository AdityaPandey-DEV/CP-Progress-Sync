class Solution {
 public:
  int countMajoritySubarrays(vector<int>& nums, int target) {
    int n = nums.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      unordered_map<int, int> freq;
      for (int j = i; j < n; j++) {
        freq[nums[j]]++;
        int size = j - i + 1;
        if (freq[target] > size / 2) {
          cnt++;
        }
      }
    }
    return cnt;
  }
};