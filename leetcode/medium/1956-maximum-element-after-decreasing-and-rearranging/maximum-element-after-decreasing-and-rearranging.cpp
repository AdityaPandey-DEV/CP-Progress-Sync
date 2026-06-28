class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(begin(arr),end(arr));
        arr[0]=1;
        for(int i=0;i<arr.size()-1;i++){
            if(arr[i+1]>arr[i]){
                arr[i+1]=arr[i]+1;
            }
            if(arr[i+1]<arr[i]){
                arr[i+1]=arr[i]-1;
            }
        }
        return *max_element(begin(arr),end(arr));
    }
};