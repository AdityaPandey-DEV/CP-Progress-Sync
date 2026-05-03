class Solution {
public:
    bool rotateString(string s, string goal) {
        int n=s.size()-1;
        for(int j=0;j<=n;j++){
        int a=s[n];
        for(int i=n;i>0;i--){
            int b=s[i-1];
            s[i-1]=a;
            a=b;
        }
        s[n]=a;
        if(s==goal)return true;
        }
        return false;
    }
};