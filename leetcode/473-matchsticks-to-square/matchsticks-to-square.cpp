class Solution {
    vector<int> nums;
    int n;
    int target;
    unordered_set<string> st;
    using ll = long long;
    bool rec(int i, vector<int>& side) {
        if (i == n) {
            for (int j = 0; j < 4; j++) {
                if(side[j]!=target)return false;
            }
            return true;
        }
        string curr = to_string(i);
        for (int j = 0; j < 4; j++) {
            curr += ",";
            curr += to_string(side[j]);
        }
        if (st.count(curr))
            return false;
        for (int j = 0; j < 4; j++) {
            if (side[j] + nums[i] <= target) {
                side[j] += nums[i];
                if(rec(i + 1, side))return true;
                side[j] -= nums[i];
            }
        }
        st.insert(curr);
        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        vector<int> side(4, 0);
        nums = matchsticks;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0)
            return false;
        target = sum / 4;
        n = nums.size();
        sort(nums.rbegin(),nums.rend());
        return rec(0, side);
    }
};