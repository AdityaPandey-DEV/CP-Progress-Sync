class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        int n=4;
        unordered_map<char,int>mp;
        for(int i=0;i<n;i++){
            for(int j=0;j<=i+2;j++){
                
                if(s1[i]==s2[i]){
                    continue;
                }
                
                if(j-i==2&&s1[i]==s2[j]){
                    swap(s2[i],s2[j]);
                }
                

            }
        }
        if(s1==s2){
            return true;
        }
        else{
            return false;
        }
    }
};