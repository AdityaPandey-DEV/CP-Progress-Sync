class Solution {
    int solve(int l,int r,vector<int>& cuts,vector<vector<int>>&dp){
        if(r-l<=1){
            return 0;
        }
        if(dp[l][r]!=-1){
            return dp[l][r];
        }
        int ans=1e9;
        for(int i=l+1;i<r;i++){
            int cost=cuts[r]-cuts[l]+solve(l,i,cuts,dp)+solve(i,r,cuts,dp);
            ans=min(cost,ans);
        }
        return dp[l][r]= ans;
    }
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(),cuts.end());
        cuts.insert(cuts.begin(),0);
        cuts.push_back(n);
        int size=cuts.size();
        vector<vector<int>>dp(size+1,vector<int>(size+1,-1));
        return solve(0,size-1,cuts,dp);


    }
};