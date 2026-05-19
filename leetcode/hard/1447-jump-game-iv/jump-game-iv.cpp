class Solution {
public:
    int minJumps(vector<int>& arr) {
        int N = arr.size();
        unordered_map<int, vector<int>> mp;
        queue<int> q;
        for (int i = 0; i < N; i++) {
            mp[arr[i]].push_back(i);
        }

        int steps = 0;
        q.push(0);
        vector<bool> vis(N, false);
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int curr = q.front();
                q.pop();
                if (curr == N - 1)
                    return steps;
                int left = curr - 1;
                int right = curr + 1;

                if (left >= 0 && !vis[left]){
                    q.push(left);
                    vis[left]=true;
                }
                    

                if (right <= N - 1 && !vis[right]){
                    q.push(right);
                    vis[right]=true;
                }
                auto vc = mp[arr[curr]];
                for (auto v : vc) {
                    if(!vis[v]){
                        q.push(v);
                        vis[v] = true;
                    }  
                }
                mp.erase(arr[curr]);
            }
            steps++;
        }
        return -1;
    }
};