class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int dis=0;
        int n=colors.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(colors[i]!=colors[j]){
                    dis=max(dis,abs(i-j));
                }
            }
        }
        return dis;
    }
};