class Solution {
public:
    int ans=0;
    int minMoves(int target, int maxDoubles) {
        int result=0;
        while(maxDoubles>0 && target!=1){
            if(target%2!=0) result++;
            target=target/2;
            result++;
            maxDoubles--;
        }
        result=result+(target-1);
        return result;
    }
};