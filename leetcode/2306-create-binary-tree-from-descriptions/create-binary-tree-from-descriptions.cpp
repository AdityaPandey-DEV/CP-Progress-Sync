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
    unordered_map<int, TreeNode*> mp;
    unordered_set<int> childs;
    TreeNode* create(int n) {
        TreeNode* root = new TreeNode();
        root->val = n;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    // TreeNode* find(TreeNode* root, int i) {
    //     if (root == NULL) {
    //         return NULL;
    //     }
    //     if (root->val == i) {
    //         return root;
    //     }

    //     TreeNode* n1 = find(root->right, i);
    //     if (n1 != NULL) {
    //         return n1;
    //     }

    //     TreeNode* n = find(root->left, i);
    //     if (n != NULL) {
    //         return n;
    //     }

    //     return NULL;
    // }
    void insert(TreeNode* root, vector<int> d) {
        TreeNode* parent = mp[d[0]];
        TreeNode* child = mp[d[1]];
        TreeNode* head = root;
        if (parent == NULL) {
            parent=mp[d[0]] = create(d[0]);
        }
        if (child == NULL) {
            child=mp[d[1]] = create(d[1]);
        }

        if (d[2] == 1) {
            parent->left = child;

        } else {
            parent->right = child;
        }
        childs.insert(d[1]);
    }

public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        TreeNode* root = NULL;
        for (auto d : descriptions) {
            insert(root, d);
        }
        for (auto& d : descriptions) {
            if (!childs.count(d[0]))
                return mp[d[0]];
        }
        return nullptr;
    }
};