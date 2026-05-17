class Solution {
    vector<bool>vis;
    int n;
    void dfs(vector<int>& arr, int i){
        if(i<0||i>=n||vis[i]){
            return ;
        }
        vis[i]=true;
        dfs(arr,i+arr[i]);
        dfs(arr,i-arr[i]);
    }
public:
    bool canReach(vector<int>& arr, int start) {
        n=arr.size();
        vis.assign(n,false);
        dfs(arr,start);
        
        for(int i=0;i<n;i++){
            if(vis[i]&&arr[i]==0){
                return true;
            }
        }

        return false;
    }
};