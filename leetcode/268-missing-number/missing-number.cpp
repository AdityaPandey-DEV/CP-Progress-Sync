class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n=nums.size();
        int xorALL=0;
        for(int i=0;i<n;i++){
            xorALL^=nums[i];
            xorALL^=i;
        }
        xorALL^=n;
        return xorALL;
    }
};