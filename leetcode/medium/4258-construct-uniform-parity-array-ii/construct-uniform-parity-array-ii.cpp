class Solution {
 public:
  bool uniformArray(vector<int>& nums) {
    int mn = *min_element(begin(nums), end(nums));
    if (mn % 2 == 0) {
      for (auto n : nums) {
        if (n % 2 != 0) {
          return false;
        }
      }
    }
    return true;
  }
};