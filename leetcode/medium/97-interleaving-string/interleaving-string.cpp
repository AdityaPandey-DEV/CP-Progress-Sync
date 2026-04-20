class Solution {
    bool rec(string s1, string s2, string s3,int i,int j,vector<vector<int>>&dp){
        
        
        // if(s1==""&&s2==""&&s3=="") return true;
        if(i<0&&j<0)return true;
        // if(i<0||j<0||k<0) return false;
        int k=i+j+1;
        bool ans1=false,ans2=false;
        if(i >= 0 && j >= 0 &&dp[i][j]!=-1){
            return dp[i][j];
        }
        if(i>=0&&s1[i]==s3[k]){
            cout<<1<<", ";
            ans1=rec(s1,s2,s3,i-1,j,dp);
        }
        if(j>=0&&s2[j]==s3[k]){
            cout<<2<<", ";
            ans2=rec(s1,s2,s3,i,j-1,dp);
        }
        if (i >= 0 && j >= 0)
            dp[i][j] = ans1 || ans2;

        return ans1 || ans2;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1=s1.size(),n2=s2.size(),n3=s3.size();
        vector<vector<int>>dp(n1+1,vector<int>(n2+1,-1));
        
        if(n1+n2!=n3){
            return false;
        } if (n1 == 1 && n2 == 0) return s1 == s3;
        if (n1 == 0 && n2 == 1) return s2 == s3;
        return rec(s1,s2,s3,s1.size()-1,s2.size()-1,dp);
    }
};