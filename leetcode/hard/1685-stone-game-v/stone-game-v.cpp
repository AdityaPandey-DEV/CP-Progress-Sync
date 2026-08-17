class Solution {
    vector<vector<int>> dp;
    int n;
    vector<int> pref;
    int solve(int l, int r) {
        if (l >= r) {
            return 0;
        }
        if(dp[l][r]!=-1){
            return dp[l][r];
        }
        int ans = 0;
        for (int mid = l; mid < r; mid++) {
            int left = pref[mid] - (l ? pref[l - 1] : 0);
            int right = pref[r] - pref[mid];
            if (left > right) {
                ans = max(ans, right+solve(mid + 1, r));
            } else if (right > left) {
                ans = max(ans, left+solve(l, mid));
            } else {
                ans = max({ans, right+solve(mid + 1, r ),
                           left+solve(l, mid)});
            }
        }
        return dp[l][r]=ans;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        int score = 0;
        int n = stoneValue.size();
        dp.assign(n, vector<int>(n, -1));
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += stoneValue[i];
            pref.push_back(sum);
        }
        return solve(0, n - 1);
    }
};