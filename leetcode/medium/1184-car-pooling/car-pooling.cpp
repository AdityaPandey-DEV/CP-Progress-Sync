class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int,int>event;
        for(auto &t:trips){
            event[t[1]]+=t[0];
            event[t[2]]-=t[0];
        }
        int c=0;
        int maxc=0;
        for(auto &e:event){
            c+=e.second;
            if(c>maxc){
                maxc=c;
            }
        }
        return capacity>=maxc;
    }
};