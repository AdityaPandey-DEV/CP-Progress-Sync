class Solution {
 public:
  vector<int> validSequence(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();
    int i = n1 - 1, j = n2 - 1;
    vector<int> suffixMatchCnt(n1 + 1, 0);
    while (i >= 0) {
      suffixMatchCnt[i] = suffixMatchCnt[i + 1];
      if (j >= 0 && word1[i] == word2[j]) {
        suffixMatchCnt[i]++;
        j--;
      }
      i--;
    }
    vector<int> ans;
    i = 0, j = 0;
    bool canChange = true;
    while (i < n1 && j < n2) {
      if (word1[i] == word2[j]) {
        ans.push_back(i);
        j++;
      } else if (canChange && suffixMatchCnt[i + 1] >= n2 - j - 1) {
        ans.push_back(i);
        j++;
        canChange = false;
      }
      i++;
    }
    if (j == n2) return ans;
    return {};
  }
};