/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
    int ans=0;
    
    int findD(TreeNode* root){
        if(root==NULL){
            return 0;
        }
        int left=findD(root->left);
        int right=findD(root->right);
        ans=max(ans,left+right);
        return 1+max(right,left);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int d=findD(root);
        return ans;
    }
};