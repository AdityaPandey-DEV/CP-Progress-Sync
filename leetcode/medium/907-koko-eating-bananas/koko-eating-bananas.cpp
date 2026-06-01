class Solution {
    
    bool canEat(vector<int>& piles,int h,int k){
        int n=piles.size();
        long long  time=0;
        for(int i=0;i<n;i++){
            if(piles[i]<k){
                time +=1;
            }
            else{
                time+=piles[i]/k;
                if(piles[i]%k>0){
                    time+=1;
                }
            }
        }
        if(time<=h){
            return true;
        }
        return false;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low =1,high=*max_element(begin(piles),end(piles));
        int mid;
        while(low<high){
            mid=low+(high-low)/2;
            if(canEat(piles,h,mid)){
                high=mid;
            }
            else{
                low=mid+1;
            }
            cout<<"LOW->"<<low<<"MID->"<<mid<<"high-->"<<high<<endl;
        }
        return low;
    }
};