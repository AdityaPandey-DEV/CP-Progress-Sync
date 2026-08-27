class Solution {
    string ans;
    string target;
    int n;
    map<char,int>mp;
    bool solve(int i,bool greater){
        if(i==n)return greater;
        if(mp.find(target[i])!=mp.end()&&mp[target[i]]>0&&!greater){
            // cout<<i<<" "<<mp[target[i]]<<endl;
            ans[i]=target[i];
            mp[target[i]]--;
            if(solve(i+1,false))return true;
            mp[target[i]]++;
        }
        for(auto p:mp){
            if(!greater&&p.first<=target[i])continue;
            if(p.second>0){
                cout<<i<<" "<<p.first<<" "<<p.second<<endl;
                char ch=p.first;
                ans[i]=ch;
                mp[ch]--;
                if(solve(i+1,true))return true;
                mp[ch]++;
            }
        }
        return false;
    }
public:
    string lexGreaterPermutation(string s, string target) {
        this->target=target;
        n=s.size();
        ans=s;
        for(auto ch:s){
            mp[ch]++;
        }
        // if(ans<target)return "";
        if(solve(0,false))return ans;
        return "";
    }
};