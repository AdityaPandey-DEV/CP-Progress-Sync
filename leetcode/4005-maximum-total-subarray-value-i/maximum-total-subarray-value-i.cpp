class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int max=*max_element(nums.begin(),nums.end());
        int min=*min_element(nums.begin(),nums.end());
        int diff=max-min;
        return (long long)diff*k;
    }
};