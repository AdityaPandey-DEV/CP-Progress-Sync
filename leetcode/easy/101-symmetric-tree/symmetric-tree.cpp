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
  bool isMirror(TreeNode* a, TreeNode* b) {
    bool ans = true;
    if (a == NULL && b == NULL) {
      return true;
    }
    if (a == NULL || b == NULL) {
      return false;
    }
    if (a->val != b->val) ans = false;
    ans &= isMirror(a->left, b->right);
    ans &= isMirror(a->right, b->left);
    return ans;
  }

 public:
  bool isSymmetric(TreeNode* root) { return isMirror(root->left, root->right); }
};