class Solution {
public:
    void rotate(vector<vector<int>>& m) {
        int n=m.size();
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                int temp=m[j][i];
                m[j][i]=m[i][j];
                m[i][j]=temp;
            }
        }
        for(int i=0;i<n;i++){
            int left=0,right=n-1;
            while(left<right){
                int temp=m[i][left];
                m[i][left]=m[i][right];
                m[i][right]=temp;
                left++;
                right--;
            }
        }
    }
};