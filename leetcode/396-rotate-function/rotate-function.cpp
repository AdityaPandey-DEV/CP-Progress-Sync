class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n=nums.size();
        int sum=0;
        int f=0;
        for(int t=0;t<n;t++){
            sum += nums[t];
        }
        for(int t=0;t<n;t++){
            f += t*nums[t];
        }
        int a=f;
        for(int i=1;i<n;i++){
            f=f+sum-(n*nums[n-i]);
            a=max(f,a);
        }
        return a;
    }
    };
