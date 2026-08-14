class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<char,int>mp;
        int ans=0;
        int i=0,j=0;
        int n=s.size();
        while(j<n){
            mp[s[j]]++;
            while(mp[s[j]]>2){
                mp[s[i]]--;
                i++;
            }
            j++;
            ans=max(ans,j-i);
        }
        return ans;
    }
};