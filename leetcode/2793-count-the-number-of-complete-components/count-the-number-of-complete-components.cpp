class Solution {
    bool isConnected(vector<vector<int>>&adj,int i,vector<bool>&vis){
        bool ans=false;
        queue<int>q;
        q.push(i);
        vis[i]=true;
        int nodes=0;
        int edges=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            nodes++;
            edges+=adj[u].size();
            for(auto v:adj[u]){
                if(vis[v]){
                    ans=true;
                    continue;
                }
                q.push(v);
                cout<<"visited"<<v<<endl;
                vis[v]=true;
                
            }
        }
        edges/=2;

        return edges==nodes*(nodes-1)/2;
        
    }
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>>adj(n);
        vector<bool>vis(n,false);
        for(auto&e:edges){
            int u=e[0];
            int v=e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    
        int ans=0;
        for(int i=0;i<n;i++){
            // cout<<"start "<<i<<endl;
            if(!vis[i]&&isConnected(adj,i,vis)){
                // cout<<"component "<<i<<endl;
                ans++;
                
                
            }
            
            // cout<<"Done "<<i<<endl;
        }
        return ans;

    }
};