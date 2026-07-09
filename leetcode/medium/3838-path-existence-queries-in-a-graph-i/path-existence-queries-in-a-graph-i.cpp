class DSU{
    vector<int>parent;
    vector<int>size;
    public:
    DSU(int n){
        parent.resize(n);
        size.assign(n,1);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int find(int u){
        if(parent[u]==u){
            return u;
        }
        return parent[u]=find(parent[u]);
        
        
    }
    void uni(int u,int v){
        u=find(u);
        v=find(v);
        if(u==v) return;
        if(size[u]<size[v]){
            swap(u,v);
        }
        parent[v]=u;
        size[u]+=size[v];
    }
};

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        DSU dsu(n);
        for(int i=0;i<n-1;i++){
            if(abs(nums[i]-nums[i+1])<=maxDiff){
                dsu.uni(i,i+1);
            }
        }
        vector<bool>ans;
        for(auto &q:queries){
            int u=q[0];
            int v=q[1];
            u=dsu.find(u);
            v=dsu.find(v);
            if(u==v){
                ans.push_back(true);
            }
            else{
                ans.push_back(false);
            }
        }
        return ans;
    }
};