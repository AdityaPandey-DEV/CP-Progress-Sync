class Solution {
 public:
  int numberOfSpecialChars(string word) {
    unordered_map<char, pair<bool, bool>> vis;
    for (auto c : word) {
      if (isupper(c)) {
        vis[tolower(c)].second = true;
      } else {
        vis[c].first = true;
      }
    }
    int ans = 0;
    for (auto p : vis) {
      if (p.second.first && p.second.second) {
        ans++;
      }
    }
    return ans;
  }
};