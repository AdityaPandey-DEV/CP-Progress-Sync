class Tree {
    vector<pair<int, int>> segTree;
    vector<int> lazy;
    public:
    Tree(int n) {
        segTree.resize(4 * n);
        lazy.resize(4 * n);
    }
    void update(int i, int l, int r, int start, int end, int val) {
        if (lazy[i] != 0) {
            segTree[i].first += lazy[i];
            segTree[i].second += lazy[i];
            if (l != r) {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        //[l,r] [start,end] [l,r]
        if (r < start || l > end)
            return;
        if (start <= l && r <= end) {
            segTree[i].first += val;
            segTree[i].second += val;
            if (l != r) {
                lazy[2 * i + 1] += val;
                lazy[2 * i + 2] += val;
            }
            return;
        }
        int mid = l + (r - l) / 2;
        update(2 * i + 1, l, mid, start, end, val);
        update(2 * i + 2, mid + 1, r, start, end, val);
        segTree[i].first =
            min(segTree[2 * i + 1].first, segTree[2 * i + 2].first);
        segTree[i].second =
            max(segTree[2 * i + 1].second, segTree[2 * i + 2].second);
        return;
    }
    int query(int i, int l, int r) {
        if (lazy[i] != 0) {
            segTree[i].first += lazy[i];
            segTree[i].second += lazy[i];
            if (l != r) {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        if(segTree[i].first>0||segTree[i].second<0) return -1;
        if(l==r)return l;
        int mid=l+(r-l)/2;
        int left=query(2*i+1,l,mid);
        if(left!=-1){
            return left;
        }
        return query(2*i+2,mid+1,r);
    }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        Tree s(n);
        vector<int>cumulativeSum(n,0);
        int maxL=0;
        unordered_map<int,int>mp;
        for(int r=0;r<n;r++){
            int val=(nums[r]%2==0)?1:-1;
            int prev=-1;
            if(mp.count(nums[r])){
                prev=mp[nums[r]];
            }
            if(prev!=-1){
                s.update(0,0,n-1,0,prev,-val);
            }
            s.update(0,0,n-1,0,r,val);
            int l=s.query(0,0,n-1);
            if(l!=-1){
                maxL=max(maxL,r-l+1);
            }
            mp[nums[r]]=r;
        }
        return maxL;
    }
};