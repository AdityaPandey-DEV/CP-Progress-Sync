class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int mod=1e9+7;
        int n=nums.size();
        vector<int>event(n,0);
        for(auto &r:requests){
            event[r[0]]+=1;
            if(r[1]+1<n)event[r[1]+1]-=1;
        }
        for(int i=1;i<n;i++){
            event[i]+=event[i-1];
        }
        sort(begin(nums),end(nums),greater<int>());
        sort(begin(event),end(event),greater<int>());
        long long ans=0;
        for(int i=0;i<n;i++){
            ans+=(1ll*event[i]*nums[i]);
            ans%=mod;
        }
        return ans;
    }
};