class Solution {
    int reverse(int n){
        long long ans=0;
        while(n>0){
            ans*=10;
            int i=n%10;
            ans+=i;
            n/=10;
        }
        return ans;
    }
public:
    int minMirrorPairDistance(vector<int>& nums) {
        int ans=INT_MAX;
        int n=nums.size();
        unordered_map<int,int>mp;
        for(int i=0;i<n;i++){
            int r=reverse(nums[i]);
            // cout<<mp[r]<<endl;
            if(mp.find(nums[i])!=mp.end()){
                ans=min({ans,abs(i-mp[nums[i]])});
                // cout<<abs(i-mp[r])<<endl;
            }
            mp[r] = i;
            cout<<abs(i-mp[r])<<endl;
        }
        return (ans==INT_MAX)?-1:ans;
        
    }
};