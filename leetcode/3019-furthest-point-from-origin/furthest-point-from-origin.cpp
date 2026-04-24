class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        unordered_map<int,int>mp;
        for(auto c:moves){
            mp[c]++;
        }
        int l=mp['L'];
        int r=mp['R'];
        int etc=mp['_'];
        return (l>r)?(l+etc)-r:(r+etc)-l;
    }
};