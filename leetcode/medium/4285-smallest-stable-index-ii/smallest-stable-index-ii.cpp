class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int>pref(n+1);
        vector<int>suff(n+1);
        pref[0]=nums[0];
        suff[n-1]=nums[n-1];
        for(int i=1;i<n;i++){
            pref[i]=max(pref[i-1],nums[i]);
            suff[n-i-1]=min(suff[n-i],nums[n-i-1]);
        }
        for(int i=0;i<n;i++){
            int a=pref[i]-suff[i];
            // cout<<pref[i]<<" - "<<suff[i]<<" = "<<a<<" ";
            if(a<=k){
               return i;
            }
        }
        return -1;
    }
};