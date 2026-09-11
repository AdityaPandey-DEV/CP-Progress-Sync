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
using t=tuple<int,int>;
class Solution {
    t rec(TreeNode* root){
        if(root==NULL)return {0,0};
        t left=rec(root->left);
        t right=rec(root->right);
        int take=root->val+get<1>(left)+get<1>(right);
        int notTake=max(get<0>(left),get<1>(left))+max(get<0>(right),get<1>(right));
        
        return {take,notTake};
    }
public:
    int rob(TreeNode* root) {
        auto [take,notTake]=rec(root);
        return max(take,notTake);
    }
};