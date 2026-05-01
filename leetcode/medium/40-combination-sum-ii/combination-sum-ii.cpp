class Solution {
    vector<vector<int>>ans;
    void solve(int idx,int& target,vector<int>&path,vector<int>& candidates){
        int n=candidates.size();
        
        if(target==0){
            ans.push_back(path);
            return ;
        }
        
        for(int i=idx;i<n;i++){
            if(candidates[i] > target) break;
            if(i>idx&&candidates[i]==candidates[i-1]) continue;
            target-=candidates[i];
            path.push_back(candidates[i]);
            solve(i+1,target,path,candidates);
            target+=candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<int>path;
        solve(0,target,path,candidates);
        return ans;
    }
};