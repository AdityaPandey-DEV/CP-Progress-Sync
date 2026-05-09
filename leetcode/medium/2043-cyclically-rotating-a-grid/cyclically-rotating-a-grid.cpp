class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int r1=0;//row
        int r2=m-1;
        int c1=0;//colunms
        int c2=n-1;
        while(r1<r2&&c1<c2){
        vector <int>temp((r2-r1)*2+(c2-c1)*2);//tempary array
        int pi=0;
        // first cloumn
        for(int i=r1;i<=r2-1;i++){
            temp[pi]=grid[i][c1];
            pi++;
        }
        // second row
        for(int i=c1;i<=c2-1;i++){
        temp[pi]=grid[r2][i];
        pi++;
        }
        // second cloumn
        for(int i=r2;i>=r1+1;i--){
            temp[pi]=grid[i][c2];
            pi++;
        }
        // first row
        for(int i=c2;i>=c1+1;i--){
        temp[pi]=grid[r1][i];
        pi++;
        }
        //rotate array
        int rot=k%((r2-r1)*2+(c2-c1)*2);
vector <int>temp2((r2-r1)*2+(c2-c1)*2);
        int len=temp2.size();
        int index=0;
        for(int i=0;i<len;i++){
            temp2[(i+rot)%len]=temp[i];
        }
        // reputting values in vector
        // first cloumn
        for(int i=r1;i<=r2-1;i++){
            grid[i][c1]=temp2[index];
            index++;
        }
        // second row
        for(int i=c1;i<=c2-1;i++){
            grid[r2][i]=temp2[index];
            index++;
        }
        // second cloumn
        for(int i=r2;i>=r1+1;i--){
            grid[i][c2]=temp2[index];
            index++;
        }
        // first row
        for(int i=c2;i>=c1+1;i--){
            grid[r1][i]=temp2[index];
            index++;
        }
        r1++;
        r2--;
        c1++;
        c2--;
    }
    return grid;
    }
};