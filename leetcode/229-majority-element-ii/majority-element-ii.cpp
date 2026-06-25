class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int>ans;
        int n=nums.size();
        unordered_map<int,int>freq;
        for(auto n:nums){
            freq[n]++;
        }
        for(auto [x,y]:freq){
            if(y>n/3){
                ans.push_back(x);
            }
        }
        return ans;
    }
};