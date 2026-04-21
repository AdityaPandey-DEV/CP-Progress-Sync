class DSU{
  public:
    int size;
    vector<int> parent, rank;
    DSU(int size): size(size){
        parent.resize(size);
        iota(parent.begin(), parent.end(), 0);
        rank.resize(size, 0);
    } int find(int a){
        return(a == parent[a]? a : (parent[a] = find(parent[a])));
    } bool unite(int a, int b){
        int parentA = find(a), parentB = find(b);
        if (parentA == parentB) return false;
        int rankA = rank[parentA], rankB = rank[parentB];
        if (rankA < rankB) parent[parentA] = parentB;
        else if (rankB < rankA) parent[parentB] = parentA;
        else{++rank[parentA]; parent[parentB] = parentA;}
        return true;
    }
};
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        const int size = source.size();
        DSU dsu(size); int result = 0;
        for(const vector<int>& i : allowedSwaps){
            int a = i[0], b = i[1];
            dsu.unite(a, b);
        } unordered_map<int, unordered_map<int, int>> hash;
        for(int i = 0; i < size; ++i){
            int parent = dsu.find(i);
            ++hash[parent][source[i]]; ++result;
        } for(int i = 0; i < size; ++i){
            int parent = dsu.find(i);
            if (hash.count(parent) && hash[parent].count(target[i])){
                --hash[parent][target[i]]; --result;
                if (hash[parent][target[i]] == 0) hash[parent].erase(target[i]);
            }
        } return result;
    }
};