class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int col=encodedText.size()/rows;
        vector<vector<char>>vc(rows,vector<char>(col));
        for(int i=0;i<rows;i++){
            for(int j=0;j<col;j++){
                vc[i][j]=encodedText[(i*col)+j];
            }

        }
        string s;
        
        for(int stc=0;stc<col;stc++){
            int i=0, j=stc;
            while(i<rows&&j<col){
                s.push_back(vc[i][j]);
                i++;
                j++;
            }
            
        }
        int n=s.length();
        int i;
        for(i=n-1;i>=0;i--){
            if(s[i]!=' ') break;
        }
        s.erase(s.begin()+i+1,s.end());
        return s;
    }
};