class LockingTree {
    unordered_map<int,int>islock;
    vector<int> parent;
    vector<vector<int>>adj;
    void unlockChild(int num){
        islock[num]=-1;
        for(auto v:adj[num]){
            unlockChild(v);
        }
        return;
    }
    bool parentCheck(int num){
        if(islock[num]!=-1){
            return false;
        }
        if(parent[num]==-1){
            return true;
        }
        return parentCheck(parent[num]);
    }
    bool childCheck(int num){
        if(islock[num]!=-1){
            return true;
        }
        bool ans=false;
        for(auto v:adj[num]){
            ans|=childCheck(v);
        }
        return ans;
    }
public:
    LockingTree(vector<int>& parent) {
        this->parent=parent;
        int n=parent.size();
        adj.resize(n);
        for(int i=1;i<n;i++){
            adj[parent[i]].push_back(i);
        }
        for(int i=0;i<n;i++){
            islock[i]=-1;
        }
    }
    
    bool lock(int num, int user) {
        if(islock[num]!=-1){
            return false;
        }
        islock[num]=user;
        return true;
    }
    
    bool unlock(int num, int user) {
        if(islock[num]==user){
            islock[num]=-1;
            return true;
        }
        return false;
    }
    
    bool upgrade(int num, int user) {
        if(islock[num]==-1){
            if(parentCheck(num)){
                if(childCheck(num)){
                    unlockChild(num);
                    islock[num]=user;
                    return true;
                }
            }
        }
        return false;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */