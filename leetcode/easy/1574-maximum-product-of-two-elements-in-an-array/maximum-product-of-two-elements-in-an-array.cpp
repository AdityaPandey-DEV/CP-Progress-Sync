class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int l1 = 1, l2 = 1;
        for (int num : nums) {
            if (num >= l1) {
                l2 = l1;
                l1 = num;
            } else if (num >= l2) {
                l2 = num;
            }
        }
        return (l2 - 1) * (l1 - 1);
    }
};