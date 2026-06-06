class Solution {
    void print(vector<int>& nums){
        int n=nums.size();
        for(int i=0;i<n;i++){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n=nums.size();
        vector<int>leftSum(n,0),rightSum(n,0),answer(n,0);
        for(int i=0;i<n;i++){
            if(i==0){
                leftSum[i]=nums[i];
                rightSum[n-i-1]=nums[n-i-1];
            }
            else{
                leftSum[i]=leftSum[i-1]+nums[i];
                rightSum[n-i-1]=rightSum[n-i]+nums[n-i-1];
            }
        }
        print(leftSum);
        print(rightSum);
        
        for(int i=0;i<n;i++){
            answer[i] = abs(leftSum[i] - rightSum[i]);
        }
        return answer;
    }
};