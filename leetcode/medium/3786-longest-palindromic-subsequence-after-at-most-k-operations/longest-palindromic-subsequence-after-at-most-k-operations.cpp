class Solution {
    int k;
    string s;
    vector<vector<vector<int>>>dp;
    int rec(int i,int j,int cost){
        // cout<<i<<" "<<j<<" "<<cost<<endl;
        if(i==j)return 1;
        if(i>j)return 0;
        if(dp[i][j][cost]!=-1)return dp[i][j][cost];
        int a=s[i]-'a',b=s[j]-'a';
        int diff=min(abs(b-a),26-abs(a-b));
        int take=0;
        if(cost+diff<=k)take=2+rec(i+1,j-1,cost+diff);
        int notTake=max(rec(i,j-1,cost),rec(i+1,j,cost));
        return dp[i][j][cost]=max(take,notTake);
    }
public:
    int longestPalindromicSubsequence(string s, int k) {
        this->s=s;
        this->k=k;
        int n=s.size();
        dp.assign(n,vector<vector<int>>(n,vector<int>(k+1,-1)));
        return rec(0,n-1,0);
    }
};