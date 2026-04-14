class Solution {
    typedef long long ll;
    long long  rec(long long ri,long long  fi,vector<int>& robot,vector<int>&positions,vector<vector<ll>>&dp){
        if(ri>=robot.size()){
            return 0;
        }
        if(fi>=positions.size()){
            return 1e12;
        }
        if(dp[ri][fi]!=-1){
            return dp[ri][fi];
        }
        long long take=abs(robot[ri]-positions[fi])+rec(ri+1,fi+1,robot,positions,dp);
        long long notTake=rec(ri,fi+1,robot,positions,dp);
        return dp[ri][fi]=min(take,notTake);
    }
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(),robot.end());
        sort(factory.begin(),factory.end());
        vector<int>positions;
        for(int i=0;i<factory.size();i++){
            int pos=factory[i][0];
            int limit =factory[i][1];
            for(int j=0;j<limit;j++){
                positions.push_back(pos);
            }
        } 
        int n=robot.size();
        int m =positions.size();
        vector<vector<ll>>dp(n+1,vector<ll>(m+1,-1));
        return rec(0,0,robot,positions,dp);
    }
};