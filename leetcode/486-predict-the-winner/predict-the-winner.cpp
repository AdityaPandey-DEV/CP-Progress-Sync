class Solution {
    vector<int> nums;
    int check(int i,int j){
        if(i>j){
            return 0;
        }
        int takei=nums[i]+min(check(i+2,j),check(i+1,j-1));
        int takej=nums[j]+min(check(i,j-2),check(i+1,j-1));
        return max(takei,takej);
        
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        bool turn=true;
        int i=0,j=nums.size()-1;
        this->nums=nums;
        int p1=check(i,j);
        int total=accumulate(nums.begin(),nums.end(),0);
        int p2=total-p1;
        return p1>=p2;
    }
};