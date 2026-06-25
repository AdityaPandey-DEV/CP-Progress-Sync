class Solution {
  int merge(vector<int>& nums, int start, int mid, int end) {
    int cnt = 0;
    int j = mid + 1;
    for (int i = start; i <= mid; i++) {
      while (j <= end && nums[i] > 2LL * nums[j]) {
        j++;
      }
      cnt += j - (mid + 1);
    }
    vector<int> temp;
    j = mid + 1;
    int i = start;

    while (i <= mid && j <= end) {
      if (nums[i] <= nums[j]) {
        temp.push_back(nums[i]);
        i++;
      } else {
        // if(nums[i] > (long long)2 * nums[j]){
        //     cnt+=(mid-i+1);
        // }
        temp.push_back(nums[j]);
        j++;
      }
    }
    while (i <= mid) {
      temp.push_back(nums[i]);
      i++;
    }
    while (j <= end) {
      temp.push_back(nums[j]);
      j++;
    }
    for (int i = 0; i < temp.size(); i++) {
      nums[start + i] = temp[i];
    }
    return cnt;
  }
  int mergeSort(vector<int>& nums, int start, int end) {
    if (start < end) {
      int mid = start + (end - start) / 2;
      int left = mergeSort(nums, start, mid);
      int right = mergeSort(nums, mid + 1, end);
      int curr = merge(nums, start, mid, end);
      return left + right + curr;
    }
    return 0;
  }

 public:
  int reversePairs(vector<int>& nums) {
    int n = nums.size() - 1;
    int ans = mergeSort(nums, 0, n);
    // for(int i=0;i<n;i++){
    //     for(int j=i+1;j<n;j++){
    //         if(nums[i]>(long long)2*nums[j]){
    //             ans++;
    //         }
    //     }
    // }
    return ans;
  }
};