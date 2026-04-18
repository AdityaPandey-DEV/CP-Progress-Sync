class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        int maxSum=-1e4;
        int sum=-1e4;
        for(int i=0;i<n;i++){
            sum=max(nums[i],nums[i]+sum);
            maxSum=max(sum,maxSum);
        }
        return maxSum;
    }
};