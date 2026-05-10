class Solution {
    int n;
    int rec(int i,vector<int>& nums,int target,vector<int>& dp){
        if(i==n-1){
            return 0;
        }
        if(dp[i]!=-1){
            return dp[i];
        }
        int ans=-1e9;
        for(int j=i+1;j<n;j++){
            if(abs(nums[j]-nums[i])<=target){
                ans=max(ans, 1+rec(j,nums,target,dp));
            }
        }
        return dp[i]=(ans<0)?-1e9:ans;
    }
public:
    int maximumJumps(vector<int>& nums, int target) {
        n=nums.size();
        vector<int>dp(n,-1e9);
        dp[n-1]=0;
        
        for(int i=n-2;i>=0;i--){
            int a=-1e9;
            for(int j=i+1;j<n;j++){
                if(abs(nums[j]-nums[i])<=target&&dp[j]!=-1e9){
                    a=max(a, 1+dp[j]);
                }
            }
            dp[i]=a;
            
        }
        int ans=dp[0];
        return (ans<0)?-1:ans;

    }
};