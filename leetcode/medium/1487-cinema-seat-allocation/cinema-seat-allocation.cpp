class Solution {
 public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    unordered_map<int, set<int>> mp;
    for (auto& r : reservedSeats) {
      mp[r[0]].insert(r[1]);
    }
    int cnt = 2 * n;
    for (auto [row, seat] : mp) {
      bool l = true, m = true, r = true;
      for (int i = 2; i <= 5; i++) {
        if (seat.count(i)) {
          l = false;
          break;
        }
      }
      for (int i = 4; i <= 7; i++) {
        if (seat.count(i)) {
          m = false;
          break;
        }
      }
      for (int i = 6; i <= 9; i++) {
        if (seat.count(i)) {
          r = false;
          break;
        }
      }
      if (l && r) {
      } else if (l || r || m) {
        cnt -= 1;
      } else {
        cnt -= 2;
      }
    }
    return cnt;
  }
};