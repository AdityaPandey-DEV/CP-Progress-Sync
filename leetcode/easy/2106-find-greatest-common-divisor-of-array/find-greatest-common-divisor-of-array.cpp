class Solution {
 public:
  int findGCD(vector<int>& nums) {
    int maxe = *max_element(begin(nums), end(nums));
    int mine = *min_element(begin(nums), end(nums));
    return gcd(maxe, mine);
  }
};