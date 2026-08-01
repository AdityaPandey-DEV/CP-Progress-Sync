class Solution {
    vector<int> nums;
    vector<vector<vector<int>>>dp;
    bool check(int i,int j,int p1,int p2,int turn){
        if(i>j){
            return p1>=p2;
        }
        
        if(turn){
            bool ans=false;
                ans|=check(i+1,j,p1+nums[i],p2,!turn);   
                ans|=check(i,j-1,p1+nums[j],p2,!turn);
                return ans;
                
            }
            else{
                bool ans=true;
                ans&=check(i,j-1,p1,p2+nums[j],!turn);
                ans&=check(i+1,j,p1,p2+nums[i],!turn); 
                return ans;
            }
        
        
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        bool turn=true;
        int i=0,j=nums.size()-1;
        int p1=0,p2=0;
        this->nums=nums;
        return check(i,j,p1,p2,turn);
    }
};