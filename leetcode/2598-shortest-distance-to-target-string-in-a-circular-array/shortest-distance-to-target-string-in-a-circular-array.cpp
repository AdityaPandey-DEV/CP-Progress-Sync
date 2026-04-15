class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        int n=words.size();
        int ans=INT_MAX;
        for(int i=0;i<n;i++){
            
            if(words[i]==target){
                int distance=min(abs(startIndex-i),n-abs(startIndex-i));
                ans=min(ans,distance);
            }
            
        }
        if(ans!=INT_MAX){
            return ans;
        }
        else{
            return -1;
        }
    }
};