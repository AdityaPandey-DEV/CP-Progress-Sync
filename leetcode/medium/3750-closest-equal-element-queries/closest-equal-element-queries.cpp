class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n=nums.size();
        int m=queries.size();
        unordered_map<int,vector<int>>mp;
        for(int i=0;i<n;i++){
            mp[nums[i]].push_back(i);
        }
        vector<int> ans;
        for(int q:queries){
            vector<int>&v=mp[nums[q]];
            if(v.size()==1){
                ans.push_back(-1);
                continue;
            }
            int idx=lower_bound(v.begin(),v.end(),q)-v.begin();
            int res=INT_MAX;
            int next=v[(idx+1)%v.size()];
            int diff1 = abs(q - next);
            res=min({res,diff1,n-diff1});
            int pre=v[(idx-1+v.size())%v.size()];
            int diff2 = abs(q - pre);
            res=min({res,diff2,n-diff2});
            ans.push_back(res);

        }
        return ans;
    }
};