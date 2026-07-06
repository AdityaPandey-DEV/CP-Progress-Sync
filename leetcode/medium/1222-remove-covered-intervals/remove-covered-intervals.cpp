class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        vector<vector<int>>ans;
        int n=intervals.size();
        sort(intervals.begin(), intervals.end(),[](auto &a, auto &b) {return (a[0] == b[0])? a[1] > b[1]:a[0] < b[0];});
        ans.push_back(intervals[0]);
        for(int i=1;i<n;i++){
            int a=ans.back()[0];
            int b=ans.back()[1];
            int c=intervals[i][0];
            int d=intervals[i][1];
            if(a<=c&&d<=b){
                continue;
            }
            ans.push_back(intervals[i]);
        }
        return ans.size();
    }
};