class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum=0;
        int n=nums.size();
        int l=0;
        int r=0;
        double maxAvg=INT_MIN;
        while(r<n){
            sum+=nums[r];
            r++;
            while(r-l>k){
                sum-=nums[l];
                l++;
            }
            if(r-l==k)
            maxAvg=max((double)sum/k,maxAvg);
            
            


        }
        return maxAvg;
    }
};