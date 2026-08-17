// 7-> [1,6][2,5][3,4]
// 8->[1,7][2,6][3,5][4,4]
// 9->[1,8][2,7][3,6][4,5]
// 10->[1,9][2,8][3,7][4,6][5,5]
class Solution {
public:
    int integerBreak(int n) {
        vector<int>dp(n+1);
        dp[0]=0;
        dp[1]=1;
        dp[2]=1;
        for(int i=3;i<=n;i++){
            for(int j=0;j<i;j++){
                dp[i]=max({dp[i],j*(i-j),j*dp[i-j]});
            }
        }
        return dp[n];
    }
};