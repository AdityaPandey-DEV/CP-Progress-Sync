class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int>last(26);
        int n=s.size();
        for(int i=0;i<n;i++){
            last[s[i]-'a']=i;
        }
        vector<bool>used(26,false);
        string ans;
        for(int i=0;i<n;i++){
            char ch=s[i];
            if(used[ch-'a'])continue;
            while(!ans.empty()&&ch<ans.back()&&last[ans.back()-'a']>i){
                used[ans.back()-'a']=false;
                ans.pop_back();
            }
            ans.push_back(ch);
            used[ch-'a']=true;
        }
        return ans;
    }
};