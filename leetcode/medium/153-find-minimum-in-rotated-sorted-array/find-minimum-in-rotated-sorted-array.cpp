class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo=0,hi=nums.size()-1,mid;
        while(hi-lo>1){
            mid=(hi+lo)/2;
            if(nums[mid]<nums[hi]){
                hi=mid;
            }else{
                lo=mid;
            }
        }
        if(nums[hi]<nums[lo]) return nums[hi];
        return nums[lo];
    }
};