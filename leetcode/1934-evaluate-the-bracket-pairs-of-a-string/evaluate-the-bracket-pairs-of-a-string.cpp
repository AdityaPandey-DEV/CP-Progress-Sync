class Solution {
    unordered_map<string,string>mp;
    string getVal(string key){
        if(mp.count(key)){
            return mp[key];
        }
        return "?";
    }
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        for(auto &k:knowledge){
            mp[k[0]]=k[1];
        }
        int n=s.size();
        string ans="";
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                i++;
                string temp="";
                while(i<n&&s[i]!=')'){
                    temp+=s[i];
                    i++;
                }
                ans+=getVal(temp);
                
            }
            else{
                ans+=s[i];
            }
        }
        return ans;
    }
};