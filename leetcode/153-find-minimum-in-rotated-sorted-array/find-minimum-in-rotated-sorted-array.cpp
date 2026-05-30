class Solution {
public:
    int findMin(vector<int>& nums) {
    int n=nums.size();
    int st=0,end=n-1,mid;
    int ans=INT_MAX;
    while(st<=end){
        mid=st+(end-st)/2;
        if(nums[st]<=nums[end]){
            ans=min(ans,nums[st]);
            return ans;
        }
        if(nums[mid]<=nums[end]){
            ans=min(ans,nums[mid]);
            end=mid-1;
        }else{
            ans=min(ans,nums[mid]);
            st=mid+1;
        }
    }
            return ans;
    }
    
};