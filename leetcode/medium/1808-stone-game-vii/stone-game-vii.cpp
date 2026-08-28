class Solution {
    //store the sum to [0,i][0,j]
    vector<int>pref;
    //i->left j->right position
    vector<vector<int>>dp;
    int rec(int i,int j){
        if(i>=j)return 0;
        if(dp[i][j]!=-1)return dp[i][j];
        // cout<<"i:- "<<i<<" j:-"<<j<<endl;
        int takeLeft=pref[j]-pref[i]-rec(i+1,j);
        int takeRight=pref[j-1]-pref[i-1]-rec(i,j-1);
        return dp[i][j]=max(takeLeft,takeRight);
    }
public:
    int stoneGameVII(vector<int>& stones) {
        int n=stones.size();
        pref.assign(n+2,0);
        pref[1]=stones[0];
        for(int i=2;i<=n;i++){
            pref[i]=pref[i-1]+stones[i-1];
        }
        dp.assign(n+2,vector<int>(n+2,-1));
        return rec(1,n);
    }
};