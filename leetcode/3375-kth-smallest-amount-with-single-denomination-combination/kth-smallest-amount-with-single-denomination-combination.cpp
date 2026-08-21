class Solution {
    using ll=long long;
    vector<int>coins;
    ll getCnt(ll x){
        int size=coins.size();
        int n=(1<<size)-1;//all ones=2^size-1
        ll cnt=0;
        for(int i=1;i<=n;i++){// from i=mask 1 to all ones 
            ll setBitsLcm=1;
            for(int j=0;j<size;j++){
                if(i&(1<<j)){
                    setBitsLcm=lcm(setBitsLcm,coins[j]);
                }
            }
            if(__builtin_popcount(i)&1){// get count of set bits
                cnt+=x/setBitsLcm;
            }
            else{
                cnt-=x/setBitsLcm;
            }
        }
        return cnt;
    }
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        this->coins=coins;
        ll l=1,r=25*2*1e9+25,ans=0;
        while(l<=r){
            ll x=l+(r-l)/2;
            ll cnt=getCnt(x);
            if(cnt<k){
                l=x+1;
            }
            else{
                ans=x;
                r=x-1;
            }
        }
        return ans;
    }
};