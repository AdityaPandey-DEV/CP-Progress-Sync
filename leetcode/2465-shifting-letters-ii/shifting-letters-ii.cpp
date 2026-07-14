class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n=s.size();
        vector<int>ans(n);
        for(auto &sh:shifts){
            int start=sh[0];
            int end=sh[1];
            int d=sh[2];
            if(d==0){
                ans[start]-=1;
                if(end+1<n)ans[end+1]+=1;
            }
            else if(d==1){
                ans[start]+=1;
                if(end+1<n)ans[end+1]-=1;
            }
        }
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=ans[i];
            ans[i]=sum;
        }
        int shift=0;
        for(int i=0;i<n;i++){
            int c=s[i]-'a';
            shift=(c+ans[i]);
            shift%=26;
            if(shift<0)shift+=26;
            s[i]=shift+'a';
        }
        return s;

    }
};