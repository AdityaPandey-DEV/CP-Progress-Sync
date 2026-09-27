class Solution {
    int i=0,n;
    string s;
    string rec(){
        string ans="";
        for(;i<n;i++){
            
            if(s[i]=='('){
                // cout<<i<<" new "<<s[i]<<endl;
                i++;
                ans+=rec();
            }
            else if(s[i]==')'){
                // cout<<i<<" return "<<s[i]<<endl;
                reverse(ans.begin(),ans.end());
                return ans;
            }
            else{
                // cout<<i<<" add "<<s[i]<<endl;
                ans+=s[i];
            }
        }
        return ans;
    }
public:
    string reverseParentheses(string s) {
        this->s=s;
        n=s.size();
        return rec();
    }
};