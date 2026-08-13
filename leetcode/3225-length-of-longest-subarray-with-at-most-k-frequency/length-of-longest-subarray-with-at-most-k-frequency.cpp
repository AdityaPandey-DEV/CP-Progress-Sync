class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int i=0,j=0;
        int n=nums.size();
        unordered_map<int,int>mp;
        int ans=0;
        while(j<n){
            mp[nums[j]]++;
            while(mp[nums[j]]>k){
                mp[nums[i]]--;
                i++;
            }
            
            j++;
            ans=max(ans,j-i);
        }
        return ans;
    }
};