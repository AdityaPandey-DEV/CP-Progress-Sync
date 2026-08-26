class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        bool dp[1000][1000];
        string ans = "";
        int start = 0, len = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j]) {
                    if (j - i <= 1) {
                        dp[i][j] = true;
                    } else
                        dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = false;
                }
                if (dp[i][j] && len < j - i + 1) {
                    start = i;
                    len = j - i + 1;
                }
            }
        }
        return s.substr(start, len);
    }
};