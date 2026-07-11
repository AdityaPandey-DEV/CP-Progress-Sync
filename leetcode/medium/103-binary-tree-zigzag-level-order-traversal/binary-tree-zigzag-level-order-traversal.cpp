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
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == NULL) return {};
    vector<vector<int>> ans;
    stack<TreeNode*> curr, next;
    bool ltr = true;
    curr.push(root);
    vector<int> a;
    while (!curr.empty()) {
      TreeNode* t = curr.top();
      curr.pop();

      if (t) {
        a.push_back(t->val);
      }
      if (ltr) {
        if (t->left != NULL) {
          next.push(t->left);
        }
        if (t->right) {
          next.push(t->right);
        }
      } else {
        if (t->right) {
          next.push(t->right);
        }
        if (t->left) {
          next.push(t->left);
        }
      }
      if (curr.empty()) {
        ltr = !ltr;
        swap(curr, next);
        ans.push_back(a);
        a.clear();
      }
    }
    return ans;
  }
};