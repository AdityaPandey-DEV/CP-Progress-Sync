class Solution {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    int n = nums.size();
    int maxe = *max_element(begin(nums), end(nums)) + k;
    map<int, int> diff;
    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++) {
      int l = max(nums[i] - k, 0);
      int r = min(nums[i] + k, maxe);
      diff[l]++;
      diff[r + 1]--;
      diff[nums[i]] += 0;
      freq[nums[i]]++;
    }
    int ans = 0;
    int csum = 0;
    for (auto& [target, sum] : diff) {
      csum += sum;
      sum = csum;
      int targetFreq = freq[target];
      int need = csum - targetFreq;
      int maxPossible = min(need, numOperations);
      ans = max(ans, targetFreq + maxPossible);
    }
    return ans;
  }
};