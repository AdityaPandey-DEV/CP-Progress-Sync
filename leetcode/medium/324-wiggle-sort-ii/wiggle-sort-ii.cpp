class Solution {
 public:
  void wiggleSort(vector<int>& nums) {
    vector<int> temp = nums;
    int n = nums.size();
    sort(temp.begin(), temp.end());
    int i = (n + 1) / 2 - 1, j = n - 1, k = 0;
    while (k < n) {
      if (k % 2 == 0) {
        nums[k] = temp[i];
        i--;
      } else {
        nums[k] = temp[j];
        j--;
      }
      k++;
    }
    return;
  }
};