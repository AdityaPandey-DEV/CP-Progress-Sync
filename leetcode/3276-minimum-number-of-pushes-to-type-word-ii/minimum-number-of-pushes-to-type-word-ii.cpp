class Solution {
public:
    int minimumPushes(string word) {
        int ans=0;
        int n=word.size();
        int i=1;
        unordered_map<char,int>mp;
        vector<int>freq(26,0);
        for(int i=0;i<n;i++){
            freq[word[i]-'a']++;
        }
        priority_queue<pair<int,char>>pq;
        for(int i=0;i<26;i++){
            if(freq[i]!=0){
                pq.push({freq[i],('a'+i)});
            }
        }
        while(!pq.empty()){
            int size=mp.size();
            // cout<<size<<endl;
            char ch=pq.top().second;
            int cnt=pq.top().first;
            pq.pop();
            if(mp.find(ch)==mp.end()){
                int s=((size/8)+1);
                // cout<<word[i]<<":-"<<s<<endl;
                mp[ch]+=s;
            }
        }
        for(int i=0;i<n;i++){
            ans+=mp[word[i]];
        }
        return ans;
    }
};