class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i=0;
        int j=0;
        int dis=0;
        int n=nums1.size();
        int m=nums2.size();
        while(i<nums1.size()&&j<nums2.size()){
            if(nums1[i] <= nums2[j]){
                dis=max(dis,j-i);
                
                j++;
            }
            else{
                i++;
            }
           
            
            
        }
        return dis;

        
    }
};