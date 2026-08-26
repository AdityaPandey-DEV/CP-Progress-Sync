class Solution {
    string get(string a, string b) {
        if(a.size()!=b.size()){
            return a.size()<b.size()?a:b;
        }
        return min(a,b);
    }

public:
    string shortestBeautifulSubstring(string s, int k) {
        unordered_map<char, int> mp;
        int i = 0, j = 0, n = s.size();
        string ans(n, '1');
        // cout << n << endl;
        bool ok = true;
        while (true) {
            if (mp['1'] == k) {
                // cout<<s.substr(i,j-i)<<endl;
                while(s[i]=='0'){
                mp[s[i]]--;
                i++;
                }
                ans = get(ans, s.substr(i, j - i));
                ok = false;
                mp[s[i]]--;
                i++;
            } else if(j<n) {
                mp[s[j]]++;
                j++;
            }
            else{
                break;
            }
            // cout << i << " " << j << " " << mp['1'] << endl;
        }
        if (ok)
            return "";
        return ans;
    }
};