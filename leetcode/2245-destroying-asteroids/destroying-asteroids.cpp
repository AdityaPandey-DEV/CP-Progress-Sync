class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        bool ans=true;
        long long m=mass;
        sort(begin(asteroids),end(asteroids));
        int n=asteroids.size();
        for(int i=0;i<n;i++){
            if(m<asteroids[i]){
                ans=false;
                break;
            }
            else{
                m+=asteroids[i];
            }
        }
        return ans;

    }
};