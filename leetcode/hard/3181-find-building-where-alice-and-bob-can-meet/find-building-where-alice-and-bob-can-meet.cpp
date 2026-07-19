class tree {
  // l,r->nums pointer
  // i->segTree
  // start,end ->range
  vector<int> nums;
  vector<int> segTree;

 public:
  tree(vector<int>& heights) {
    nums = heights;
    int n = nums.size();
    segTree.resize(4 * n);
    build(0, 0, n - 1);
  }
  void build(int i, int l, int r) {
    if (l == r) {
      segTree[i] = l;
      return;
    }
    int mid = l + (r - l) / 2;
    build(2 * i + 1, l, mid);
    build(2 * i + 2, mid + 1, r);
    segTree[i] = (nums[segTree[2 * i + 1]] > nums[segTree[2 * i + 2]])
                     ? segTree[2 * i + 1]
                     : segTree[2 * i + 2];
  }
  int query(int i, int start, int end, int l, int r) {
    if (l > end || r < start) {
      return -1;
    }
    if (l >= start && r <= end) {
      return segTree[i];
    }
    int mid = l + (r - l) / 2;
    int left = query(2 * i + 1, start, end, l, mid);
    int right = query(2 * i + 2, start, end, mid + 1, r);
    if (left == -1) return right;
    if (right == -1) return left;
    return (nums[left] > nums[right]) ? left : right;
  }
};

class Solution {
 public:
  vector<int> leftmostBuildingQueries(vector<int>& heights,
                                      vector<vector<int>>& queries) {
    vector<int> ans;
    int n;
    tree s(heights);
    n = heights.size();
    for (auto& q : queries) {
      int a = q[0];
      int b = q[1];
      if (a > b) swap(a, b);
      if (a == b || heights[b] > heights[a]) {
        ans.push_back(b);
        continue;
      }
      int result = -1;
      int l = b + 1;
      int r = n - 1;
      while (l <= r) {
        int mid = l + (r - l) / 2;
        int idx = s.query(0, b + 1, mid, 0, n - 1);
        if (idx != -1 && heights[idx] > heights[a]) {
          result = idx;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      ans.push_back(result);
    }
    return ans;
  }
};