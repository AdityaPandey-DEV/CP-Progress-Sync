class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<int,long long>event;
        for(auto &s:segments){
            event[s[0]]+=s[2];
            event[s[1]]-=s[2];
        }
        auto it=event.begin();
        long long sum=it->second;
        int start=it->first;
        it++;
        vector<vector<long long>>ans;
        for(;it!=event.end();it++){
            if(sum>0)ans.push_back({start,it->first,sum});
            sum+=it->second;
            start=it->first;
        }
        return ans;
    }
};