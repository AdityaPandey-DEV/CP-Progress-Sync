class Solution {
    int rows;
    int col;
    vector<vector<int>>at;
    int cub(vector<pair<int,int>>&arr,int target){
        int n=arr.size();
        int l=0;
        int r=n-1;
        int ans=0;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(arr[mid].first<=target){
                l=mid+1;
                ans=mid;
            }
            else{
                r=mid-1;
            }
        }
        return ans;

    }
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>>arr(n);
        for(int i=0;i<n;i++){
            arr[i]={nums[i],i};
        }
        sort(arr.begin(),arr.end());
        vector<int>nodetoIdx(n);
        for(int i=0;i<n;i++){
            int node=arr[i].second;
            nodetoIdx[node]=i; 
        }
        rows=n;
        col=log2(n)+1;
        at.resize(rows,vector<int>(col,0));
        for(int node=0;node<n;node++){
            int fioh=cub(arr,arr[node].first+maxDiff);
            at[node][0]=fioh;
        }
        for(int j=1;j<col;j++){
            for(int node=0;node<rows;node++){
                at[node][j]=at[at[node][j-1]][j-1];
            }
        }
        vector<int>ans;
        for(auto &q:queries){
            int u=q[0];
            int v=q[1];
            int a=nodetoIdx[u];
            int b=nodetoIdx[v];
             if(a==b){
                ans.push_back(0);
                continue;
            }
            if(a>b){
                swap(a,b);
            }
            int curr=a;
            int jumps=0;
            for(int j=col-1;j>=0;j--){
                if(at[curr][j]<b){
                    curr=at[curr][j];
                    jumps+=(1<<j);
                }

                
            }
            if(at[curr][0]>=b){
                ans.push_back(jumps+1);
            }
            else{
                ans.push_back(-1);
            }
        
           
        }
        return ans;

    }
};