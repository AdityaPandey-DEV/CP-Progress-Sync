#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int n;
    int offset;
    vector<vector<int>> dp;

    int ts(const vector<int>& nums, int target, int i, int curr) {
        if (i == n) return (curr == target);

        int idx = curr + offset;
        if (idx < 0 || idx >= dp[i].size()) return 0;

        if (dp[i][idx] != -1) return dp[i][idx];

        int add = ts(nums, target, i + 1, curr + nums[i]);
        int sub = ts(nums, target, i + 1, curr - nums[i]);

        dp[i][idx] = add + sub;
        return dp[i][idx];
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        n = nums.size();
        int S = 0;
        for (int x : nums) S += x;

        if (abs(target) > S) return 0;

        offset = S;
        dp.assign(n, vector<int>(2 * S + 1, -1));

        return ts(nums, target, 0, 0);
    }
};