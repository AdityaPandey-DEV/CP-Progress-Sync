class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        using index=pair<int,int>;
        deque<index>q;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]==0){
                    q.push_back({i,j});
                }
            }
        }
        while(!q.empty()){
            index i=q.front();
            q.pop_front();
            int a=i.first;
            int b=i.second;
            for(int i=0;i<n;i++){
                matrix[i][b]=0;
            }
            for(int i=0;i<m;i++){
                matrix[a][i]=0;
            }
        }
    }
};