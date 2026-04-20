class Solution {
public:
    int dp[50001][2];
    int rec(vector<int>& prices, int i, int canBuy, int fee) {
        if (i == prices.size())
            return 0;
        if (dp[i][canBuy] != -1)
            return dp[i][canBuy];
        int profit = 0;
        if (canBuy) {
            int buy = -prices[i] + rec(prices, i + 1, 0, fee);
            int skip = rec(prices, i + 1, 1, fee);
            profit = max(buy, skip);
        } else {
            int sell = prices[i] - fee + rec(prices, i + 1, 1, fee);
            int skip = rec(prices, i + 1, 0, fee);
            profit = max(sell, skip);
        }
        return dp[i][canBuy] = profit;
    }
    int maxProfit(vector<int>& prices, int fee) {
        memset(dp, -1, sizeof(dp));
        return rec(prices, 0, 1, fee);
    }
};