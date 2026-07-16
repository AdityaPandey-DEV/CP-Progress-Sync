class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n=nums.size();
        int maxe=0;
        vector<int>prefixGcd(n);
        for(int i=0;i<n;i++){
            maxe=max(maxe,nums[i]);
            prefixGcd[i]=gcd(nums[i],maxe);
        }
        sort(begin(prefixGcd),end(prefixGcd));
        int i=0,j=n-1;
        long long sum=0;
        while(i<j){
            sum+=gcd(prefixGcd[i],prefixGcd[j]);
            i++;
            j--;
        }
        return sum;
    }
};