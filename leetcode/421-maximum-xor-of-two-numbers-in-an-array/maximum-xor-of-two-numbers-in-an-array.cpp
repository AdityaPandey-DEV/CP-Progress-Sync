class Solution {
    struct Trie{
        Trie*left;
        Trie*right;
    };
    void insert(Trie*root,int num){
        Trie*curr=root;
        for(int i=31;i>=0;i--){
            int ithBit=(num>>i)&1;
            if(ithBit==0){
                if(curr->left==NULL){
                    curr->left=new Trie();
                    
                }
                curr=curr->left;
            }
            else{
                if(curr->right==NULL){
                    curr->right=new Trie();
                    
                }
                curr=curr->right;
            }
        }
        
    }
    int get(Trie*root,int num){
        int ans=0;
        Trie*curr=root;
        for(int i=31;i>=0;i--){
            int ithBit=(num>>i)&1;
            if(ithBit==0){
                if(curr->right!=NULL){
                    curr=curr->right;
                    ans=ans|1<<i;
                    
                }
                else if(curr->left!=NULL){
                    curr=curr->left;
                }
                else{
                    return ans;
                }
                
            }
            else{
                if(curr->left!=NULL){
                    curr=curr->left;
                    ans=ans|1<<i;
                    
                }
                else if(curr->right!=NULL){
                    curr=curr->right;
                }
                else{
                    return ans;
                }
            }
        }
        return ans;
        
    }
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie* root=new Trie();
        int n=nums.size();
        int maxAns=0;
        for(int i=0;i<n;i++){
            insert(root,nums[i]);
        }
        for(int j=0;j<n;j++){
            maxAns=max(maxAns,get(root,nums[j]));
        }
        return maxAns;
    }
};