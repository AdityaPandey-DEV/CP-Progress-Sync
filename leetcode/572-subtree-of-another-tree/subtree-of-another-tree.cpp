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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==NULL&&q==NULL){
            return true;
        }
        if(p==NULL||q==NULL){
            return false;
        }

        bool ans=false;
        if(p->val==q->val){
            ans=true;
        }
        ans=ans&&isSameTree(p->right,q->right);
        ans=ans&&isSameTree(p->left,q->left);
        return ans;
        
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root==NULL){
            return false;
        }
        if(isSameTree(root,subRoot)) return true;

        return isSubtree(root->left,subRoot)||isSubtree(root->right,subRoot);
    }
};