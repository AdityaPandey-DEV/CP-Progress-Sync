class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int a=0,b=arr.size()-1;
        while(b-a+1>k){
            if(abs(arr[a]-x)>abs(arr[b]-x)){
                a++;
            }
            else if(abs(arr[a]-x)<abs(arr[b]-x)||abs(arr[a]-x)==abs(arr[b]-x)){
                b--;
            }
        }
        vector<int>ans(arr.begin()+a,arr.begin()+b+1);
        return ans;
    }
};