class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans=0;
        int n=prices.size();
        int bestBuy=prices[0];
        for(int i=1;i<n;i++){
            bestBuy=min(prices[i-1],bestBuy);
            ans=max(ans,prices[i]-bestBuy);
            
        }
        return ans;
    }
};