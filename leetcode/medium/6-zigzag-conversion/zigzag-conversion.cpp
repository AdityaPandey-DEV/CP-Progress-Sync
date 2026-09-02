class Solution {
public:
    string convert(string s, int numRows) {
        int n=s.size();
        if(numRows==1||numRows>=n)return s;
        vector<string>vs(numRows,string(n,' '));
        int j=0,k=0;
        for(int i=0;i<n;){
            while(j<numRows){
                if(i<n)vs[j][k]=s[i];
                j++;
                i++;
            }
            j=numRows-2;
            k++;
            while(j>0){
                if(i<n)vs[j][k]=s[i];
                k++;
                j--;
                i++;
            }
        }
        string ans;
        for(auto s:vs){
            cout<<s<<endl;
            for(auto ch:s){
                if(ch!=' '){
                    ans+=ch;
                }
            }
        }
        return ans;
    }
};