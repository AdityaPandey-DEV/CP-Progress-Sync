class Tree {
    vector<int> segTree; //[NoOfZero]
    vector<int> nums;
    public:
    Tree(vector<int>&zero) {
        nums=zero;
        int n=nums.size();
        segTree.resize(4*n);
        build(0, 0, n - 1);
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
    //query[start,end]
    //[l,r][start,end][l,r]
    //[start, l,r,   end]
    int query(int i,int l,int r,int start,int end){
        if(l>end||r<start){
            return 0;
        }
        if(start<=l&&r<=end){
            return segTree[i];
        }
        int mid=l+(r-l)/2;
        auto left= query(2*i+1,l,mid,start,end);
        auto right= query(2*i+2,mid+1,r,start,end);
        return max(left,right);

    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n=s.size();
        vector<int>bit,len,start,finish;
        for(int i=0;i<n;){
            int j=i;
            while(j<n&&s[i]==s[j])j++;
            bit.push_back(s[i]-'0');
            len.push_back(j-i);
            start.push_back(i);
            finish.push_back(j-1);
            i=j;
        }
        
        int m=len.size();
        vector<int>zero(m,0);
        for(int i=1;i<m-1;i++){
            if (bit[i]==1)
            zero[i]=len[i-1]+len[i+1];
        }
        Tree sg(zero);

        int totalOne=count(begin(s),end(s),'1');
        vector<int>ans;
        for (auto q : queries) {
            int l = q[0];
            int r = q[1];
            int u = lower_bound(finish.begin(), finish.end(), l) - finish.begin();
            int v = upper_bound(start.begin(), start.end(), r) - start.begin() - 1;
            int bestGain = 0;
            int x = u + 1;
            if (x < m && x <= v - 1 && bit[x] == 1) {
                int leftZeros = finish[x - 1] - l + 1;
                int rightZeros = min(finish[x + 1], r) - start[x + 1] + 1;
                bestGain = max(bestGain, leftZeros + rightZeros);
            }
            int y = v - 1;
            if (y >= 0 && y >= u + 1 && bit[y] == 1) {
                int leftZeros = finish[y - 1] - max(start[y - 1], l) + 1;
                int rightZeros = r - start[y + 1] + 1;
                bestGain = max(bestGain, leftZeros + rightZeros);
            }
            bestGain = max(bestGain, sg.query(0, 0, m - 1, u + 2, v - 2));
            ans.push_back(totalOne + bestGain);
        }
        return ans;
    }
};