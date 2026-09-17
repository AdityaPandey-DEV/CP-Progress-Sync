class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int i = 0, j = 0, n = arr.size();
        vector<int> last(n, INT_MAX);
        int sum = 0;
        int ans = INT_MAX;

        while (j < n) {
            // cout << "start:-" << i << " " << j << " sum:-" << sum << endl;
            sum += arr[j];
            while (sum > target) {
                sum -= arr[i];
                i++;
            }
            if (j > 0)
                last[j] = last[j - 1];
            if (sum == target) {
                cout << i << " " << j << endl;
                int len = j - i + 1;
                if (i > 0 && last[i - 1] != INT_MAX) {
                    ans = min(ans, len + last[i - 1]);
                }
                last[j] = min(len, last[j]);
            }

            j++;
            // cout << "end:-" << i << " " << j << " sum:-" << sum << endl;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};