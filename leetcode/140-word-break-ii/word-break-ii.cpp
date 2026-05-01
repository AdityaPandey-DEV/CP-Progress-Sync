class Solution {
    vector<string>ans;
    unordered_set<string>st;
    void solve(int idx,string path,string s){
        int n=s.size();
        if(idx==n){
            ans.push_back(path);
            
        }
        for(int i=idx;i<n;i++){
            string temp=s.substr(idx,i-idx+1);
            if(st.count(temp)){
                string newpath=(path.empty())?temp:path+" "+temp;
                solve(i+1,newpath,s);
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n=s.size();
        string path;
        for(auto a:wordDict){
            st.insert(a);
        }
        solve(0,path,s);
        return ans;
    }
};