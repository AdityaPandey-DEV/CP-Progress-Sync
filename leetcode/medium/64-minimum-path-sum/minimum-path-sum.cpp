class Solution {
    int rec(vector<vector<int>>& grid,int i,int j,vector<vector<int>>&dp){
        int n=grid.size();
        int m=grid[0].size();
        if(i==n-1&&j==m-1){
            return dp[i][j]=grid[i][j];
        }
        if(i==n||j==m){
            return 1e9;
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        int down=grid[i][j]+rec(grid,i+1,j,dp);
        int right=grid[i][j]+rec(grid,i,j+1,dp);
        return dp[i][j]=min(down,right);
    }
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,-1));
        return rec(grid,0,0,dp);
    }
};