class Solution {
public:
    int findMin(vector<int>& nums) {
    int n=nums.size();
    int st=0,end=n-1,mid;
    int ans=INT_MAX;
    int id;
    while(st<=end){
        mid=st+(end-st);
        if(nums[mid]<=nums[end]){
            if(nums[mid]<ans){
            ans=nums[mid];
}
            end=mid-1;
        }else{
            if(nums[mid]<ans){
            ans=nums[mid];}
            st=mid+1;
        }
    }
    return ans;
    }
};