class Solution {
    vector<string>transform(vector<int>& arr){
        vector<string> ans;
        for(auto x:arr){
            
            ans.push_back(to_string(x));
        }
        return ans;
    }
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        vector<string> ans1=transform(arr1);
        vector<string> ans2=transform(arr2);
        int ans=0;
        unordered_map<string,int>heap;
        for(auto s:ans1){
            int n=s.size();
            for(int i=1;i<=n;i++){
                // if(s.substr(0,i)=="") continue;
                heap[s.substr(0,i)]=i;
            }
        }
        for(auto s:ans2){
            int n=s.size();
            for(int i=1;i<=n;i++){
                if(heap.find(s.substr(0,i))!=heap.end()){
                    ans=max(ans,heap[s.substr(0,i)]);
                    cout<<heap[s.substr(0,i)]<<'\n';
                }
            }
        }
        return ans;
    }
};