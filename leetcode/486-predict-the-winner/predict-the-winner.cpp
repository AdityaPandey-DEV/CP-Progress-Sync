class Solution {
    vector<int> nums;
    vector<vector<int>>dp;
    int check(int i,int j){
        if(i>j){
            return 0;
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        int takei=nums[i]+min(check(i+2,j),check(i+1,j-1));
        int takej=nums[j]+min(check(i,j-2),check(i+1,j-1));
        return dp[i][j]=max(takei,takej);
        
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        bool turn=true;
        int i=0,j=nums.size()-1;
        this->nums=nums;
        dp.assign(j+1,vector<int>(j+1,-1));
        int p1=check(i,j);
        int total=accumulate(nums.begin(),nums.end(),0);
        int p2=total-p1;
        return p1>=p2;
    }
};