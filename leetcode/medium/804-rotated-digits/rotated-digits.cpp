class Solution {
public:
    int rotatedDigits(int m) {
        int k = 0;
        for(int n=1;n<=m;n++){
        int l=n;
        bool changed = 0;
        bool valid =1;

        while(l>0){
           int i=l%10;
    if (i==2||i==5||i==6||i==9) changed = true;
    if (i==3||i==4||i==7)valid=false;
        l /=10;
        }
        if(changed&&valid) k++;
        }
        return k;
    }
};