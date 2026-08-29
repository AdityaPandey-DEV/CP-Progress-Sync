class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<int>vec=nums;
        //sort the vec
        sort(begin(vec),end(vec));
        int grp=0;
        unordered_map<int,int>noToGroup;
        unordered_map<int,deque<int>>groupToNo;
        noToGroup[vec[0]]=grp;
        groupToNo[grp].push_back(vec[0]);
        int n=nums.size();
        for(int i=1;i<n;i++){
            if(abs(vec[i]-vec[i-1])>limit){
                grp++;
            }
            noToGroup[vec[i]]=grp;
            groupToNo[grp].push_back(vec[i]);
        }
        //build the ans -merge the group
        vector<int>ans(n);
        for(int i=0;i<n;i++){
            int num=nums[i];
            int grp=noToGroup[num];
            //smallest awailable no in this group
            ans[i]=groupToNo[grp].front();// use ho gaya delete element
            groupToNo[grp].pop_front();
        }
        return ans;
    }
};