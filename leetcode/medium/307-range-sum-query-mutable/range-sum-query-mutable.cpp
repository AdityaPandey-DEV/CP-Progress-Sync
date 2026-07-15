class NumArray {
  int blockSize;
  vector<int> block;
  vector<int> nums;

 public:
  NumArray(vector<int>& input) {
    nums = input;
    int n = nums.size();
    blockSize = ceil(sqrt(n));
    int noOfBlock = (n + blockSize - 1) / blockSize;
    block.assign(noOfBlock, 0);
    for (int i = 0; i < n; i++) {
      block[i / blockSize] += nums[i];
    }
  }

  void update(int index, int val) {
    int updateBlockNo = index / blockSize;
    block[updateBlockNo] -= nums[index];
    nums[index] = val;
    block[updateBlockNo] += val;
  }

  int sumRange(int left, int right) {
    int startBlock = (left / blockSize);
    int endBlock = right / blockSize;
    int sum = 0;
    if (startBlock == endBlock) {
      for (int i = left; i <= right; i++) {
        sum += nums[i];
      }
    } else {
      int startBlockEnd = (startBlock + 1) * blockSize - 1;
      for (int i = left; i <= startBlockEnd; i++) {
        sum += nums[i];
      }
      for (int b = startBlock + 1; b <= endBlock - 1; b++) {
        sum += block[b];
      }
      int endBlockStart = endBlock * blockSize;
      for (int i = endBlockStart; i <= right; i++) {
        sum += nums[i];
      }
    }
    return sum;
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */