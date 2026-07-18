class Solution {
 public:
  vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
    int n = nums.size();
    int m = queries.size();
    int maxe = *max_element(begin(nums), end(nums));
    vector<int> freq(maxe + 1, 0);
    for (int i = 0; i < n; i++) {
      int num = nums[i];
      for (int j = 1; j * j <= num; j++) {
        if (num % j == 0) {
          freq[j]++;
          if (num / j != j) {
            freq[num / j]++;
          }
        }
      }
    }
    vector<long long> cnt(maxe + 1, 0);
    for (int g = maxe; g >= 1; g--) {
      long long count = freq[g];
      cnt[g] = (count * (count - 1)) / 2;
      for (int mul = 2 * g; mul <= maxe; mul += g) {
        cnt[g] -= cnt[mul];
      }
    }
    vector<long long> pref(maxe + 1, 0);
    for (int g = 1; g <= maxe; g++) {
      pref[g] = pref[g - 1] + cnt[g];
    }
    vector<int> ans;
    for (auto idx : queries) {
      int l = 1;
      int r = maxe;
      int temp = 1;
      while (l <= r) {
        int mid = (l + (r - l) / 2);
        if (pref[mid] > idx) {
          temp = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      ans.push_back(temp);
    }
    return ans;
  }
};