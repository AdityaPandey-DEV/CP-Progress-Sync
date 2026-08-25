class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int mul=1;
        set<int>st(nums.begin(),nums.end());
        while(st.count(mul*k)){
            mul++;
        }
        return mul*k;
    }
};