class Solution {
public:
    bool isGood(vector<int>& nums) {
        int size=nums.size();
        vector<int>count(500);
        for(auto i:nums){
            if(i>size-1){
                return false;
            }
            count[i]++;
        }
        for(int i=1;i<size-2;i++){
            cout<<i<<"->"<<count[i]<<endl;
            if(count[i]!=1){
                return false;
            }
            
        }
        if(count[size-1]!=2){
            return false;
        }
        return true;
    }
};