class Solution {
    vector<vector<int>>dp;
    int rec(int i,int j,int m, int n){
        if(i<0||i>m||j<0||j>n){
            return 0;
        }
        if(i==0&&j==0){
            return 1;
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        return dp[i][j]=rec(i-1,j,m,n)+rec(i,j-1,m,n);
    }
public:
    int uniquePaths(int m, int n) {
        dp.assign(m,vector<int>(n,-1));
        return rec(m-1,n-1,m,n);
    }
};