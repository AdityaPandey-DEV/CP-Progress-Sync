class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char,int>count;
        int ans=0;
        for(auto c:word){
            
            if(islower(c)){
                
                count[c]++;
            }
        }
        for(auto c:word){
            if(islower(c)){
                count[c]--;
            }
            else{
                
                if(count.find(tolower(c))!=count.end()){
                    cout<<count[tolower(c)]<<endl;
                    if(count[tolower(c)]==0&&count.find(c)==count.end()){
                        
                        ans++;
                    }
                }
                count[c]=1;
            }
        }
        return ans;
    }
};