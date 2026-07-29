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
class Solution {
  int rec(TreeNode* root, int maxe) {
    if (root == NULL) {
      return 0;
    }
    maxe = max(root->val, maxe);
    int s = rec(root->left, maxe) + rec(root->right, maxe);
    if (maxe == root->val) s++;
    return s;
  }

 public:
  int goodNodes(TreeNode* root) { return rec(root, -1e9); }
};