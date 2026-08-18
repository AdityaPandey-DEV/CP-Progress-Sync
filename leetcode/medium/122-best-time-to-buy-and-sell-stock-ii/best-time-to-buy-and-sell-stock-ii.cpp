class Solution {
    vector<int>prices;
    int n;
    vector<vector<int>>dp;
    int buy(int i,bool canBuy){
        int profit=0;
        if(i==n){
            return 0;
        }
        if(dp[i][canBuy]!=-1)return dp[i][canBuy];
        if(canBuy){
            profit=max(buy(i+1,false)-prices[i],buy(i+1,true));
        }
        else{
            profit=max(buy(i+1,true)+prices[i],buy(i+1,false));
        }
        return dp[i][canBuy]=profit;
    }
public:
    int maxProfit(vector<int>& prices) {
        this->prices=prices;
        n=prices.size();
        dp.assign(n,vector<int>(2,-1));
        return buy(0,true);
    }
};