class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        queue<tuple<int,int,int,int>> q;
        int n = classroom.size(), m = classroom[0].size();
        vector<vector<int>> litterId(n,vector<int>(m, -1));
        int L = 0;
        int si=-1,sj=-1;
        // pushing the start point in queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (classroom[i][j] == 'L'){
                        litterId[i][j]=L;
                        L++;
                    }

                if (classroom[i][j] == 'S') {
                    si=i;
                    sj=j;
                    
                }
            }
        }

        // if nothing to collect return 0 moves
        if (L == 0)
            return 0;
        int fullMask=(1<<L)-1;
        vector<vector<vector<vector<bool>>>>vis(n,vector<vector<vector<bool>>>(m,vector<vector<bool>>(energy+1,vector<bool>(1<<L,false))));
        q.push({si, sj, energy, 0});
        vis[si][sj][energy][0] = true;
        vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // processing the bfs
        int level = 0;

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                auto[i,j,e,mask]=q.front();

                // cout << "i:- " << i << " j:- " << j << " e:- " << e << " l:- "
                //      << l << endl;

                q.pop();

                for (auto& d : dir) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    int ne = e-1;
                    int nm=mask;
                    if (ni >= n || ni < 0 || nj >= m || nj < 0)
                        continue;

                    if (classroom[ni][nj] == 'X')
                        continue;
                    if (ne < 0)
                        continue;
                    if (classroom[ni][nj] == 'R')
                        ne = energy;

                    if (classroom[ni][nj] == 'L') {
                        int id=litterId[ni][nj];
                        nm=mask|(1<<id);
                        
                    }
                    if(nm==fullMask){
                        return level+1;
                    }

                    // cout << "ni:- " << ni << " nj:- " << nj << " e:- " << e
                    //      << " l:- " << nm << endl;

                    if(!vis[ni][nj][ne][nm]){
                        vis[ni][nj][ne][nm]=true;
                        q.push({ni, nj, ne, nm});
                    }
                }
            }

            level++;
        }

        return -1;
    }
};