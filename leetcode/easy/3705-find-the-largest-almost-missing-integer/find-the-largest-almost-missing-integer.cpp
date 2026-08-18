class Solution {
 public:
  int largestInteger(vector<int>& nums, int k) {
    int n = nums.size();
    map<int, int> freq;
    unordered_map<int, int> mp;
    int i = 0, j = 0;
    while (j < n) {
      while (j - i + 1 > k) {
        mp[nums[i]]--;
        i++;
      }
      mp[nums[j]]++;
      if (j - i + 1 == k) {
        // cout<<"j:-"<<j<<" i:-"<<i<<endl;
        for (auto [u, v] : mp) {
          if (v > 0) {
            cout << u << endl;
            freq[u]++;
          }
        }
      }

      j++;
    }
    int ans = -1;
    for (auto it = freq.rbegin(); it != freq.rend(); it++) {
      // cout << it->first << ":" << it->second << endl;
      if (it->second == 1) {
        ans = it->first;
        break;
      }
    }
    return ans;
  }
};