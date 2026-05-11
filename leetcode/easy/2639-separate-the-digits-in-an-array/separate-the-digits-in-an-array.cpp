class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        int n=nums.size() - 1;
        vector<int> temp;
        for(int i=n;i>=0;i--){
            while (true){
                if(nums[i]==0)break;
                int a=nums[i]%10;
                temp.push_back(a);
                nums[i] /=10;
                
            }  
        }
        reverse(temp.begin(),temp.end());
        return temp;
        }
    
};