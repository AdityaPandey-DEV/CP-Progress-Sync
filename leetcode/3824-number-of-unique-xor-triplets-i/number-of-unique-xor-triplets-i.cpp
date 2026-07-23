class Solution {
    int msb(int n){
        int ans=0;
        while(n){
            n>>=1;
            ans++;
        }
        return ans;
    }
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n=nums.size();
        if(n<=2){
        unordered_set<int>s;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                for(int k=j;k<n;k++){
                    s.insert(nums[i]^nums[j]^nums[k]);
                }
            }
        }
        return s.size();
        }
        return pow(2,msb(n));
        

    }
};