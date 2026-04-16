class NumArray {
public:
int len;
vector<int>b;
vector<int> num;
    NumArray(vector<int>& nums) {
        int n=nums.size();
        len=sqrt(n)+1;
        b.assign(len+1,0);
        for(int i=0;i<n;i++){
            b[i/len]+=nums[i];
        }
        
        num=nums;
        
    }
    
    int sumRange(int left, int right) {
        int ans=0;
        for(int i=left;i<=right;){
            if(i%len==0&&i+len-1<=right){
                ans+=b[i/len];
                i+=len;
            }
            else{
                ans+=num[i];
                i++;
            }
        }
        return ans;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */