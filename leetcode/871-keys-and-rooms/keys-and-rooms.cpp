class Solution {
    int n;
    vector<bool>vis;
    void dfs(int u,vector<vector<int>>& rooms){
        vis[u]=true;
        for(auto v:rooms[u]){
            if(!vis[v])
            dfs(v,rooms);
        }
        return;
    }
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        n=rooms.size();
        vis.assign(n,false);
        dfs(0,rooms);
        for(int i=1;i<n;i++){
            if(!vis[i]){
                return false;
            }
        }
        return true;
    }
};