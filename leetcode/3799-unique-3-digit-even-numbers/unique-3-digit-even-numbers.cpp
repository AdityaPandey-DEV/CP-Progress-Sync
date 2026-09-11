class Solution {
    unordered_set<int>st;
public:
    int totalNumbers(vector<int>& digits) {
        int n=digits.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j)continue;
                for(int k=0;k<n;k++){
                    if(i==k||j==k||digits[i]==0)continue;
                    int val=digits[i]*100+digits[j]*10+digits[k];
                    if(val%2==1)continue;
                    st.insert(val);
                }
            }
        }
        return st.size();
    }
};