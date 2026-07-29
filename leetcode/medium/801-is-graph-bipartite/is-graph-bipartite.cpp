class Solution {
    vector<int>color;
    bool dfs(int u,vector<vector<int>>& graph,int c){
        color[u]=c;
        for(auto v:graph[u]){
            if(color[v]==-1){
                if(!dfs(v,graph,1-c)){
                    return false;
                }
            }
            else if(color[u]==color[v]){
                return false;
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n=graph.size();
        color.assign(n,-1);
        for(int i=0;i<n;i++){
            if(color[i]==-1&&!dfs(i,graph,0)){
                return false;
            }
        }
        return true;
        
    }
};