class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n=nums.size();
        if(n==1)return 1;
        int smallIdx=min_element(nums.begin(),nums.end())-nums.begin();
        int largeIdx=max_element(nums.begin(),nums.end())-nums.begin();
        int front=max(smallIdx+1,largeIdx+1);
        int last=max(n-smallIdx,n-largeIdx);
        int both=min(smallIdx+1+n-largeIdx,largeIdx+1+n-smallIdx);
        return min({front,last,both});
    }
};