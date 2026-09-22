struct Node{
    int prod=1;
    int cnt[5]={0};
};
class Tree{
    vector<Node>segTree;
    vector<int>nums;
    int n,k;
    void build(int i,int left,int right){
        if(left==right){
            int curr=nums[left]%k;
            segTree[i].prod=curr;
            segTree[i].cnt[curr]++;
            return;
        }
        int mid=left+(right-left)/2;
        build(2*i+1,left,mid);
        build(2*i+2,mid+1,right);
        segTree[i]=merge(segTree[2*i+1],segTree[2*i+2]);
    }
    
public:
    Tree(vector<int>&nums,int k){
        this->nums=nums;
        this->k=k;
        n=nums.size();
        segTree.assign(4*n,Node());
        build(0,0,n-1);
    }
    Node merge(Node &a,Node &b){
        Node ans;
        ans.prod=(a.prod*b.prod)%k;
        for(int i=0;i<5;i++){
            ans.cnt[i]=a.cnt[i];
        }
        for(int i=0;i<5;i++){
            int newI=(a.prod*i)%k;
            ans.cnt[newI]+=b.cnt[i];
        }
        return ans;
    }
    void update(int index,int val,int i,int l,int r){
        if(l==r){
            int oldcurr=nums[index]%k;
            nums[index]=val;
            int curr=nums[index]%k;
            segTree[i].prod=curr;
            segTree[i].cnt[oldcurr]--;
            segTree[i].cnt[curr]++;
            return;
        }
        int mid=l+(r-l)/2;
        if(index<=mid){
            update(index,val,2*i+1,l,mid);
        }
        else{
            update(index,val,2*i+2,mid+1,r);
        }
        segTree[i]=merge(segTree[2*i+1],segTree[2*i+2]);
    }
    Node query(int i,int start,int end,int l,int r){
        if(start>r||end<l){
            return Node();
        }
        if(start<=l&&end>=r){
            return segTree[i];
        }
        int mid=l+(r-l)/2;
        Node left=query(2*i+1,start,end,l,mid);
        Node right=query(2*i+2,start,end,mid+1,r);
        return merge(left,right);
    }

};
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int m=queries.size();
        int n=nums.size();
        vector<int>ans(m,0);
        int j=0;
        Tree t(nums,k);
        for(auto &q:queries){
            int index=q[0];
            int val=q[1];
            int start=q[2];
            int x=q[3];
            t.update(index,val,0,0,n-1);
            Node a=t.query(0,start,n-1,0,n-1);
            ans[j]=a.cnt[x];
            j++;
        }
        return ans;
    }
};