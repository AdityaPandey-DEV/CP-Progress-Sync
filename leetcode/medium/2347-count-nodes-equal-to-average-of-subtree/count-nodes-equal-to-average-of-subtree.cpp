/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
using pii = pair<int, int>;  //[average,NoOfNode]
int ans;
pii solve(TreeNode* root) {
  if (root == NULL) return {0, 0};
  pii left = solve(root->left);
  pii right = solve(root->right);
  int noOfNodes = 1 + left.second + right.second;
  int sum = root->val + left.first + right.first;
  int avg = sum / noOfNodes;
  if (root->val == avg) {
    ans++;
  }
  return {sum, noOfNodes};
}
class Solution {
 public:
  int averageOfSubtree(TreeNode* root) {
    ans = 0;
    solve(root);
    return ans;
  }
};