class Solution {
public:
    int search(vector<int>& nums, int target) {
        int st=0,end=nums.size()-1,mid;
        while(end-st>1){
            mid = (st+end)/2;
            if(nums[mid]==target) return mid;
            //left sorted
            if(nums[mid-1]>=nums[st]){
                if(target>=nums[st]&&target<=nums[mid-1]){
                    end=mid-1;
                }else{
                    st=mid+1;
                }
            }
            //right sorted
            else{
                if(nums[mid+1]<=target&&target<=nums[end]){
                    st=mid+1;
                }else{
                    end=mid-1;
                }
            }
        } 
        if(nums[end]==target) return end;
        else if(nums[st]==target) return st;
        else return -1;
    }
};