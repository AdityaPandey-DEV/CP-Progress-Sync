class LFUCache {
    list<int>dll;
    map<int,list<vector<int>>>freq;//key->address
    unordered_map<int,list<vector<int>>::iterator>mp;//counter->{key,val,counter}
    int capacity=0,size=0;
public:
    LFUCache(int capacity) {
        this->capacity=capacity;
    }

    void makeFreqUsed(int key){
        auto &vc=(*(mp[key]));
        int val=vc[1];
        int f=vc[2];
        freq[f].erase(mp[key]);
        if(freq[f].empty()){
            freq.erase(f);
        }
        f++;
        freq[f].push_front({key,val,f});
        mp[key]=freq[f].begin();
    }
    
    int get(int key) {
        if(mp.find(key)==mp.end()){
            return -1;
        }
        auto vc=(*(mp[key]));
        int val=vc[1];
        makeFreqUsed(key);
        return val;

    }
    
    void put(int key, int value) {
        if(capacity==0) return ;
        if(mp.find(key)!=mp.end()){
            auto &vc=*mp[key];
            vc[1]=value;
            makeFreqUsed(key);
        }
        else if(size<capacity){
            size++;
            freq[1].push_front({key,value,1});
            mp[key]=freq[1].begin();

        }
        else{
            auto &list=freq.begin()->second;
            int key_to_delete=(list.back())[0];
            list.pop_back();
            if(list.empty()){
                freq.erase(freq.begin()->first);
            }
            freq[1].push_front({key,value,1});
            mp.erase(key_to_delete);
            mp[key]=freq[1].begin();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */