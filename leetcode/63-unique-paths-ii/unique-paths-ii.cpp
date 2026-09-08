class Solution {
    vector<vector<int>>dp;
    vector<vector<int>>grid;
    int n,m;
    int dfs(int i,int j){
        if(i==n-1&&j==m-1)return 1;
        if(i>=n||j>=m)return 0;
        if(dp[i][j]!=-1)return dp[i][j];
        if(grid[i][j])return 0;
        int ni=i+1,nj=j+1;
        int ans=0;
        if(ni<n){
            ans+=dfs(ni,j);
        }
        if(nj<m){
            ans+=dfs(i,nj);
        }
        return dp[i][j]=ans;
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        grid=obstacleGrid;
        n=grid.size(),m=grid[0].size();
        if(grid[n-1][m-1])return 0;
        dp.assign(n,vector<int>(m,-1));
        return dfs(0,0);
    }
};