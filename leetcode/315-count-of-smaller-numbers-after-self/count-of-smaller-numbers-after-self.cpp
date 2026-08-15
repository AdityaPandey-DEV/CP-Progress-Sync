class Tree{
    vector<int>segTree;
    int n;
    public:
    Tree(int n){
        segTree.assign(4*20001,0);
        this->n=n;
    }

    void updateq(int i,int l,int r,int val){
        if(l==r){
            segTree[i]++;
            return;
        }
        int mid=l+(r-l)/2;
        if(val<=mid){
            updateq(2*i+1,l,mid,val);
        }
        else{
            updateq(2*i+2,mid+1,r,val);
        }
        segTree[i]=segTree[2*i+1]+segTree[2*i+2];
    }
    void update(int val){
        
        updateq(0,0,20000,val+10000);
        return;
    }
    //query->[start end]
    //l.   start   end.    r
    // [l  [start end]  r]
    int queryq(int i,int start,int end,int l,int r){
        if(r<start||l>end){
            return 0;
        }
        if(start<=l&&r<=end){
            return segTree[i];
        }
        int mid=l+(r-l)/2;
        return queryq(2*i+1,start,end,l,mid)+queryq(2*i+2,start,end,mid+1,r);
    }
    int query(int val){
        if(val<-10000)return 0;
        return queryq(0,0,val+10000,0,20000);
    }

};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n=nums.size();
        Tree st(n);
        vector<int>ans(n);
        for(int i=n-1;i>=0;i--){
            ans[i]=st.query(nums[i]-1);
            st.update(nums[i]);
        }
        return ans;
    }
};