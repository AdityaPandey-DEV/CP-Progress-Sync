class Solution {
public:
    bool judgeCircle(string moves) {
        int h=0,v=0;
        for(auto ch:moves){
            switch(ch){
                case 'U':
                v++;
                break;
                case 'D':
                v--;
                break;
                case 'R':
                h++;
                break;
                case 'L':
                h--;
                break;

            }

        }
        if(h==0&&v==0){
            return true;
        }
        return false;
    }
};