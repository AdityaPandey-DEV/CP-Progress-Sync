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
    using pii=pair<int,int>;
public:
    void getVt(TreeNode* root,int row,int hd,map<int,vector<pii>>&mp){
        if(root==NULL)return;
        mp[hd].push_back({row,root->val});
        getVt(root->left,row+1,hd-1,mp);
        getVt(root->right,row+1,hd+1,mp);
    }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>>ans;
        
        map<int,vector<pii>>mp;
        getVt(root,0,0,mp);
        for(auto &[u,v]:mp){
            vector<int>a;
            sort(v.begin(), v.end());
            for(auto p:v){
                a.push_back(p.second);
            }
            ans.push_back(a);
        }
        return ans;
    }
};