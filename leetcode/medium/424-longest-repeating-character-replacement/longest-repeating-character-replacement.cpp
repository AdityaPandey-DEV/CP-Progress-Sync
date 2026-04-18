class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char,int>mp;
        int n=s.size();
        int l=0,r=0;
        int maxSize=0;
        int maxFreq=0;
        while(r<n){
            mp[s[r]]++;
            maxFreq=max(maxFreq,mp[s[r]]);
            r++;
            while((r-l)-maxFreq>k){
                mp[s[l]]--;
                l++;
            }
            
            
            maxSize=max(maxSize,r-l);
        }
        return maxSize;
    }
};