class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size();
        int st=1,end=n-1,mid;
        if(n==1) return nums[0];
        while(st<=end){
            mid=st+(end-st)/2;
            if(nums[mid-1]!=nums[mid]&&nums[mid]!=nums[mid+1])
            return nums[mid];
            else if(mid%2==0&&nums[mid]==nums[mid+1]){
                st=mid+2;}
            else if(mid%2==1&&nums[mid]==nums[mid-1]){
                st=mid+1;
            }else{
                end=mid-1;
            }
        }
        return nums[end];
    }
};