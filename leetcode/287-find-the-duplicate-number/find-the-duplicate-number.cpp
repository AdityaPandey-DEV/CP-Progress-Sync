class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        set<int>st;
        for(auto i:nums){
            if(st.count(i)){
                return i;
            }
            st.insert(i);
        }
        return 0;
    }
};