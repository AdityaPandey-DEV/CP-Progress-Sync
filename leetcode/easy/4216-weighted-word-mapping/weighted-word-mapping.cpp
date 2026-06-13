class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string ans;
         
        for(string s:words){
            
            int sum=0;
            for (int i = 0; i < s.size(); i++) {

                sum += weights[s[i] - 'a'];

            }
            sum%=26;
            ans.push_back('z'-sum);



        }
        return ans;
    }
};