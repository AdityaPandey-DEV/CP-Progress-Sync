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
  int rec(TreeNode* root, int i) {
    int left = 1e9, right = 1e9;

    if (root->left == NULL && root->right == NULL) {
      return i;
    }
    if (root->left != NULL) {
      left = rec(root->left, i + 1);
    }
    if (root->right != NULL) {
      right = rec(root->right, i + 1);
    }
    return min(left, right);
  }

 public:
  int minDepth(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + rec(root, 0);
  }
};