class Solution {
 public:
  int characterReplacement(string s, int k) {
    int n = s.size();
    vector<int> freq(26, 0);
    int l = 0, maxfreq = 0, maxsize = 0;
    for (int r = 0; r < n; r++) {
      freq[s[r] - 'A']++;
      maxfreq = max(maxfreq, freq[s[r] - 'A']);
      int size = r - l + 1;
      while ((size)-maxfreq > k) {
        freq[s[l] - 'A']--;
        l++;
        size = r - l + 1;
      }
      maxsize = max(maxsize, size);
    }
    return maxsize;
  }
};