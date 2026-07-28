class Solution {
public:
    string smallestPalindrome(string s) {
        int n=s.size();
        if(n<2){
            return s;
        }
        vector<int>cnt(26,0);
        for(int i=0;i<n;i++){
            cnt[s[i]-'a']++;
        }
        int mid=-1;
        string ans="";
        for(int i=0;i<26;i++){
            if(cnt[i]%2==1){
                mid=i;
            }
            if(cnt[i]){
                cnt[i]/=2;
            }
            while(cnt[i]>0){
                ans+=('a'+i);
                cnt[i]--;
            }
            
        }
        string a=ans;
        reverse(a.begin(),a.end());
        if(mid!=-1){
            ans+=('a'+mid);
        }
        ans+=a;
        return ans;

    }
};