class Solution {
  vector<int> buildLPS(string b) {
    int n = b.size();
    vector<int> lps(n, 0);
    int len = 0;
    for (int i = 1; i < n; i++) {
      if (b[i] == b[len]) {
        len++;
        lps[i] = len;
      } else {
        if (len == 0) {
          lps[i] = 0;
        } else {
          i--;
          len = lps[len - 1];
        }
      }
    }
    return lps;
  }
  bool kmpSearch(string a, string b, vector<int>& lps) {
    int n = a.size();
    int m = b.size();
    int i = 0, j = 0;
    while (i < n) {
      if (a[i] == b[j]) {
        i++;
        j++;
      }
      if (j == m) {
        return true;
      } else if (a[i] != b[j]) {
        if (j != 0) {
          j = lps[j - 1];
        } else {
          i++;
        }
      }
    }
    return false;
  }

 public:
  int repeatedStringMatch(string a, string b) {
    int cnt = 1;
    vector<int> lps = buildLPS(b);
    string r = a;
    while (r.size() < b.size()) {
      r += a;
      cnt++;
    }
    if (kmpSearch(r, b, lps)) {
      return cnt;
    }
    r += a;
    cnt++;
    if (kmpSearch(r, b, lps)) {
      return cnt;
    }
    return -1;
  }
};