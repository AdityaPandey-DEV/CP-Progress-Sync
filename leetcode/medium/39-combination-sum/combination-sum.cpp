class Solution {
    vector<vector<int>>ans;
    void solve(int idx,int& target,vector<int>&path,vector<int>& candidates){
        int n=candidates.size();
        if(idx==candidates.size()||target<0){
            return ;
        }
        if(target==0){
            ans.push_back(path);
            return ;
        }
        for(int i=idx;i<n;i++){
            target-=candidates[i];
            path.push_back(candidates[i]);
            solve(i,target,path,candidates);
            target+=candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int>path;
        solve(0,target,path,candidates);
        return ans;
    }
};