class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n=arr.size();
        unordered_map<int,int>mp;
        vector<int>temp(begin(arr),end(arr));
        
        sort(begin(temp),end(temp));
        int idx=1;
        for(int i=0;i<n;i++){
            if(mp.count(temp[i]))continue;
            mp[temp[i]]=idx;
            idx++;
        }
        for(int i=0;i<n;i++){
            arr[i]=mp[arr[i]];
        }
        return arr;
    }
};