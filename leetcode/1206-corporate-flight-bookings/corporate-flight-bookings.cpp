class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int>ans(n,0);
        for(auto &b:bookings){
            int first=b[0]-1;
            int last=b[1]-1;
            int seats=b[2];
            ans[first]+=seats;
            if(last+1<n)ans[last+1]-=seats;
        }
        for(int i=1;i<n;i++){
            ans[i]+=ans[i-1];
        }
        return ans;
    }
};