class Solution {
 public:
  int numRescueBoats(vector<int>& people, int limit) {
    int n = people.size();
    int ans = 0;
    sort(people.begin(), people.end());
    int l = 0;
    int r = n - 1;
    while (l <= r) {
      ans++;
      if (people[l] + people[r] <= limit) {
        l++;
        r--;
      } else {
        r--;
      }
    }
    return ans;
  }
};