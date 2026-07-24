class Solution {
 public:
  int uniqueXorTriplets(vector<int> &nums) {
    int n = nums.size();
    int maxe = *max_element(begin(nums), end(nums));
    int limit = 1;
    while (limit <= maxe) {
      limit *= 2;
    }
    vector<bool> one(limit, false);
    for (int num : nums) {
      one[num] = true;
    }
    vector<bool> two(limit, false);
    for (int i = 0; i < limit; i++) {
      if (one[i]) {
        for (int &num : nums) {
          two[i ^ num] = true;
        }
      }
    }
    vector<bool> three(limit, false);
    for (int i = 0; i < limit; i++) {
      if (two[i]) {
        for (int &num : nums) {
          three[i ^ num] = true;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < limit; i++) {
      if (three[i]) ans++;
    }
    return ans;
  }
};