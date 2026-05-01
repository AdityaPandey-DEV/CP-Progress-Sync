class LRUCache {
    list<int>dll;
    unordered_map<int,pair<list<int>::iterator,int>>mp;
    int size=0;
    int capacity=0;
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
    }
    void makeRecentlyUsed(int key){
        dll.erase(mp[key].first);
        dll.push_front(key);
        mp[key].first=dll.begin();
    }
    int get(int key) {
        if(mp.find(key)==mp.end()){
            return -1;
        }
        makeRecentlyUsed(key);
        return mp[key].second;
    }
    
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            mp[key].second=value;
            makeRecentlyUsed(key);

        }
        else{
            dll.push_front(key);
            mp[key]={dll.begin(),value};
            size++;
        }
        if(size>capacity){
            int keyd=dll.back();
            mp.erase(keyd);
            dll.pop_back();
            size--;
        }
       
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */