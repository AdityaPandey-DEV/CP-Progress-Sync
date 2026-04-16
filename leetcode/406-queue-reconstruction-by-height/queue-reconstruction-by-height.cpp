class Solution {
    vector<int> tree;
    void build(int n,int l,int r){
        if(l==r){
            tree[n]=1;
        }
        else{
            int mid=(l+r)/2;
            build(2*n+1,l,mid);
            build(2*n+2,mid+1,r);
            tree[n]=tree[2*n+1]+tree[2*n+2];
        }
    }
    int query(int n,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)/2;
        if(tree[2*n+1]>=k){
            return query(2*n+1,l,mid,k);
        }
        else{
            return query(2*n+2,mid+1,r,k-tree[2*n+1]);
        }


    }
    void update(int n,int l,int r,int idx){
        if(l==r){
            tree[n]=0;
            return ;
        }
        int mid=(l+r)/2;
        if(idx<=mid){
            update(2*n+1,l,mid,idx);
        }
        else{
            update(2*n+2,mid+1,r,idx);
        }
        tree[n]=tree[2*n+1]+tree[2*n+2];
    }

    
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n=people.size();
        sort(people.begin(),people.end(),[](vector<int> &a,vector<int>&b){
            if(a[0]==b[0]) return a[1]>b[1];
            else return a[0]<b[0];
        });
        tree.resize(4*n);
        build(0,0,n-1);
        vector<vector<int>>ans(n);
        for(auto&p:people){
            int k=p[1];
            int pos=query(0,0,n-1,k+1);
            ans[pos]=p;
            update(0,0,n-1,pos);
        }
        return ans;
    }
};