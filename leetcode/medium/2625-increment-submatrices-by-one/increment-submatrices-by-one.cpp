class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>>diff(n,vector<int>(n,0));
        for(auto &q:queries){
            int i1=q[0];
            int j1=q[1];
            int i2=q[2];
            int j2=q[3];
            for(int i=i1;i<=i2;i++){
                diff[i][j1]+=1;
                if(j2+1<n)diff[i][j2+1]-=1;
            }
            
        }
        
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=0;j<n;j++){
                sum+=diff[i][j];
                diff[i][j]=sum;
            }
        }
        return diff;
    }
};