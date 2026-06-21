class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(begin(costs),end(costs));
        int n=costs.size();
        int i=0;
        while(coins>0&&i<n&&coins>=costs[i]){
            cout<<costs[i]<<" ";
            coins-=costs[i];
            i++;

        }
        return i;
    }
};