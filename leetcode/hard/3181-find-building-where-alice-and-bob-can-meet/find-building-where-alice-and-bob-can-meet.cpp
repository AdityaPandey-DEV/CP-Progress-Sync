class Solution {
  void buildSegmentTree(int n, int l, int r, int segmentTree[],
                        vector<int>& heights) {
    if (l == r) {
      segmentTree[n] = l;
      return;
    } else {
      int mid = (l + r) / 2;
      buildSegmentTree(2 * n + 1, l, mid, segmentTree, heights);
      buildSegmentTree(2 * n + 2, mid + 1, r, segmentTree, heights);
      int left = segmentTree[2 * n + 1];
      int right = segmentTree[2 * n + 2];
      segmentTree[n] = (heights[left] > heights[right]) ? left : right;
    }
  }
  int* constructST(vector<int>& heights, int n) {
    int* segmentTree = new int[4 * n];
    buildSegmentTree(0, 0, n - 1, segmentTree, heights);
    return segmentTree;
  }

  int query(int start, int end, int i, int l, int r, int st[],
            vector<int>& heights) {
    if (l > end || r < start) {
      return -1;
    }
    if (l >= start && r <= end) {
      return st[i];
    }
    int mid = (l + r) / 2;
    int leftIndex = query(start, end, 2 * i + 1, l, mid, st, heights);
    int rightIndex = query(start, end, 2 * i + 2, mid + 1, r, st, heights);
    if (leftIndex == -1) return rightIndex;
    if (rightIndex == -1) return leftIndex;
    return (heights[leftIndex] > heights[rightIndex]) ? leftIndex : rightIndex;
  }
  int RIMQ(int st[], vector<int>& heights, int n, int l, int r) {
    return query(l, r, 0, 0, n - 1, st, heights);
  }

 public:
  vector<int> leftmostBuildingQueries(vector<int>& heights,
                                      vector<vector<int>>& queries) {
    int n = heights.size();
    int* segmentTree = constructST(heights, n);
    vector<int> result;
    for (auto& query : queries) {
      int min_idx = min(query[0], query[1]);
      int max_idx = max(query[0], query[1]);
      if (min_idx == max_idx) {
        result.push_back(max_idx);
        continue;
      } else if (heights[min_idx] < heights[max_idx]) {
        result.push_back(max_idx);
        continue;
      }
      int l = max_idx + 1;
      int r = n - 1;
      int result_idx = INT_MAX;
      while (l <= r) {
        int mid = l + (r - l) / 2;
        int idx = RIMQ(segmentTree, heights, n, l, mid);
        if (heights[idx] > max(heights[min_idx], heights[max_idx])) {
          result_idx = min(result_idx, idx);
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      result_idx = (result_idx == INT_MAX) ? -1 : result_idx;
      result.push_back(result_idx);
    }
    return result;
  }
};