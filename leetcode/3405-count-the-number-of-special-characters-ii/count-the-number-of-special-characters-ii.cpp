class Solution {
public:
    int numberOfSpecialChars(string w) {
        int n=w.size();
        int c=0;
        unordered_map<char,int> m;
        for(int i=65;i<=90;i++){
            m[char(i)]=0;
        }
        for(int i=97;i<=122;i++){
            m[char(i)]=0;
        }
        for(int i=0;i<n;i++){
            if(isupper(w[i])){
                m[w[i]]++;
            }
            else if(islower(w[i])&&m[toupper(w[i])]>0){
                m[w[i]]=INT_MIN;
            }
            else{
                m[w[i]]++;
            }
        }
        for(int i=65;i<=90;i++){
            if(m[char(i)]>0&&m[tolower(char(i))]>0) c++;
        }
        return c;
    }
};