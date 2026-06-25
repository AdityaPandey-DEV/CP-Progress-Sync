class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int>freq;
        for(auto n:nums){
            freq[n]++;
        }
        int maxfreq=0;
        int maxNo;
        for(auto [x,y]:freq){
            if(y>maxfreq){
                maxfreq=y;
                maxNo=x;
            }
        }
        return maxNo;
    }
};