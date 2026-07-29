class Solution {
    long long ncr(int n,int r,int k){
        r=min(r,n-r);
        long long ans=1;
        for(int i=1;i<=r;i++){
            ans=ans*(n-r+i)/i;
            if(ans>=k){
                return ans;
            }
        }
        return ans;
    }
public:
    string smallestPalindrome(string s, int k) {
        int n=s.size();
        char mid='\0';
        if(n%2==1){
            mid=s[n/2];
        }
        vector<int>cnt(26,0);
        for(int i=0;i<n/2;i++){
            cnt[s[i]-'a']++;
        }
        string half;
        
        for(int i=0;i<n/2;i++){
            bool placed=false;
            for(int j=0;j<26;j++){
                if(cnt[j]>0){
                    cnt[j]-=1;//fixed the position
                    long long ways=1;
                    int letter=0;
                    for(int i=0;i<26;i++){
                        letter+=cnt[i];
                    }
                    for(int c=0;c<26;c++){
                        if(cnt[c]>0){
                            ways*=ncr(letter,cnt[c],k);
                            letter-=cnt[c];
                        }
                        if(ways>=k)break;
                    }
                    
                    if(k<=ways){
                        half.push_back('a'+j);
                        placed=true;
                        break;
                    }
                    else{
                        k=k-ways;
                        cnt[j]+=1;
                    }
                }
                
            }
            if(!placed)return "";
        }
        string rhalf=half;
        reverse(rhalf.begin(),rhalf.end());
        return half+(mid!='\0'?string(1,mid):"")+rhalf;
        
    }
};