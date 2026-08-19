class Solution {
    vector<int>merge(vector<int>& nums1, vector<int>& nums2){
        vector<int>ans;
        int n=nums1.size(),m=nums2.size();
        int i=0,j=0;
        while(i<n&&j<m){
            if(nums1[i]>nums2[j]){
                ans.push_back(nums1[i]);
                i++;
            }
            else if(nums1[i]<nums2[j]){
                ans.push_back(nums2[j]);
                j++;
            }
            else{
                if(lexicographical_compare(nums2.begin()+j,nums2.end(),nums1.begin()+i,nums1.end())){
                    ans.push_back(nums1[i]);
                    i++;
                }
                else{
                    ans.push_back(nums2[j]);
                    j++;
                }
            }
        }
        while(i<n){
            ans.push_back(nums1[i]);
            i++;
        }
        while(j<m){
            ans.push_back(nums2[j]);
            j++;
        }
        return ans;
    }
    vector<int>maxn(vector<int>& nums,int remove){
        vector<int>st;
        for(int i=0;i<nums.size();i++){
            while(!st.empty()&&st.back()<nums[i]&&remove>0){
                st.pop_back();
                remove--;
            }
            st.push_back(nums[i]);
        }
        while(remove>0){
            st.pop_back();
            remove--;
        }
        return st;
    }
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1=nums1.size(),n2=nums2.size();
        vector<int>best;
        int s=max(0,k-n2),e=min(k,n1);
        for(int i=s;i<=e;i++){
            int remove1=n1-i;
            int remove2=n2-(k-i);
            vector<int>num1=maxn(nums1,remove1);
            vector<int>num2=maxn(nums2,remove2);
            best=max(best,merge(num1,num2));
        }
        return best;
    }
};