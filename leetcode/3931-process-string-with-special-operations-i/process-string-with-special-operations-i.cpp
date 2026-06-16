class Solution {
public:
    string processStr(string s) {
        string result="";
        for(auto c:s){
            if(islower(c)){
                result.push_back(c);
            }
            if(c=='*'){
                if(result.size()<1)continue;
                result.pop_back();
            }
            if(c=='#'){
                result+=result;
            }
            if(c=='%'){
                reverse(begin(result),end(result));
            }
            // cout<<result<<endl;
        }
        return result;
    }
};