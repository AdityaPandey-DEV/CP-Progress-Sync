class Solution {
 public:
  int uniqueXorTriplets(vector<int>& nums) {
    int n = nums.size();
    unordered_set<int> s, s1;
    int max_xor = 0;
    for (int j = 0; j < n; j++) {
      for (int k = j; k < n; k++) {
        int x = nums[j] ^ nums[k];
        s.insert(x);
      }
    }
    for (int i = 0; i < n; i++) {
      for (auto num : s) {
        int x = num ^ nums[i];
        s1.insert(x);
        max_xor = max(max_xor, max_xor ^ x);
      }
    }
    return s1.size();
  }
};