struct Trie{
    int idx;
    Trie* child[26];
    ~Trie() {
            for (int i = 0; i < 26; i++) {
                delete child[i];
            }
        }
};

Trie* getNode(int i){
    Trie* temp =new Trie();
    temp->idx=i;
    for(int i=0;i<26;i++){
        temp->child[i]=NULL;

    }
    return temp;
}

void insert(Trie* root,int i,vector<string>& wordsContainer){
    string word=wordsContainer[i];
    int n=word.size();
    for(int j=n-1;j>=0;j--){
        char ch=word[j];
        int idx=ch-'a';
        if(root->child[idx]==NULL){
            root->child[idx]=getNode(i);
        }
        root=root->child[idx];
        if(wordsContainer[root->idx].size()>n){
            root->idx=i;
        }
    }
}
int search(Trie* root,string &word){
    int result_idx=root->idx;
    int n=word.length();
    for(int i=n-1;i>=0;i--){
        int idx=word[i]-'a';
        root=root->child[idx];
        if(root==NULL){
            return result_idx;
        }
        result_idx=root->idx;

    }
    return result_idx;

}


class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int m=wordsContainer.size();
        int n=wordsQuery.size();
        vector<int>ans(n);
        Trie* root=getNode(0);
        for(int i=0;i<m;i++){
            int idx=root->idx;
            if(wordsContainer[i].size()<wordsContainer[idx].size()){
                root->idx=i;
            }
            insert(root,i,wordsContainer);

        }
        for(int i=0;i<n;i++){
            ans[i]=search(root,wordsQuery[i]);
        }
        delete root;
        return ans;
    }
};