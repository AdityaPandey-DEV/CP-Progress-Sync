class Tree{
    vector<int>segTree;
    vector<int>nums;
    public:
    Tree(vector<int>nums){
        this->nums=nums;
        int n=nums.size();
        segTree.resize(4*n);
        build(0,0,n-1);
    }
    
    void build(int i,int l,int r){
        if(l==r){
            segTree[i]=nums[l];
            return;
        }
        int mid=l+(r-l)/2;
        build(2*i+1,l,mid);
        build(2*i+2,mid+1,r);
        segTree[i]=max(segTree[2*i+1],segTree[2*i+2]);
    }


    void update(int i,int l,int r,int idx){
        if(l==r){
            segTree[i]=-1;
            return ;
        }
        int mid=l+(r-l)/2;
        if(idx<=mid){
            update(2*i+1,l,mid,idx);
        }
        else{
            update(2*i+2,mid+1,r,idx);
        }
        segTree[i]=max(segTree[2*i+1],segTree[2*i+2]);
    }
    //[l,r]->nums
    //[start,end]->query
    //[l r] [start,end]  [l,r]
    //[start l  r   end  ]
    
    int query(int i,int l,int r,int start,int end){
        if(l>end||r<start){
            return -1;
        }
        if(l>=start&&r<=end){
            return segTree[i];
        }
        int mid=l+(r-l)/2;
        return max(query(2*i+1,l,mid,start,end),query(2*i+2,mid+1,r,start,end));
    }
};
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        Tree s(baskets);
        int n=baskets.size();
        int ans=0;
        for(auto i:fruits){
            int l=0;
            int r=n-1;
            int idx=-1;
            while(l<=r){
                int mid=l+(r-l)/2;
                int maxe=s.query(0,0,n-1,l,mid);
                if(maxe>=i){
                    idx=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            if(idx!=-1){
                s.update(0,0,n-1,idx);
            }
            else{
                ans++;
            }
        }
        return ans;
    }
};