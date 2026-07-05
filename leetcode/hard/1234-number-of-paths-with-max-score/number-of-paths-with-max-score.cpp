class Solution {
    int n;
    int MOD = 1e9 + 7;
    vector<vector<pair<int, int>>> t;
    bool isValid(int i, int j, vector<string>& board) {
        if (i >= 0 && i < n && j >= 0 && j < n && board[i][j] != 'X') {
            return true;
        }
        return false;
    }
    int get(char ch) { return ch != 'S' ? ch - '0' : 0; }
    pair<int, int> solve(int i, int j, vector<string>& board) {
        if (board[i][j] == 'E') {
            return {0, 1};
        }
        if (board[i][j] == 'X') {
            return {0, 0};
        }
        
        if (t[i][j].first != -1)return t[i][j];
        int us = 0, up = 0;
        int ls = 0, lp = 0;
        int ds = 0, dp = 0;
        char ch = board[i][j];
        if (isValid(i - 1, j, board)) {
            auto [score, path] = solve(i - 1, j, board);
            us = score;
            up = path;
            if (up > 0) {
                us += get(ch);
            }
        }
        if (isValid(i, j-1, board)) {
            auto [score, path] = solve(i, j-1, board);
            ls = score;
            lp = path;
            if (lp > 0) {
                ls += get(ch);
            }
        }
        if (isValid(i - 1, j-1, board)) {
            auto [score, path] = solve(i - 1, j-1, board);
            ds = score;
            dp = path;
            if (dp > 0) {
                ds += get(ch);
            }
        }

         int bestScore, bestPaths;
        if (us == ls && ls == ds) {
            bestScore = us;
            bestPaths = up + lp + dp;
        } else if (us == ls) {
            bestScore = us;
            bestPaths = up + lp;
            if (ds > bestScore || (ds == bestScore && dp > bestPaths)) {
                bestScore = ds; bestPaths = dp;
            }
        } else if (ls == ds) {
            bestScore = ls;
            bestPaths = lp + dp;
            if (us > bestScore || (us == bestScore && up > bestPaths)) {
                bestScore = us; bestPaths = up;
            }
        } else {
            bestScore = us; bestPaths = up;
            if (ls > bestScore || (ls == bestScore && lp > bestPaths)) {
                bestScore = ls; bestPaths = lp;
            }
            if (ds > bestScore || (ds == bestScore && dp > bestPaths)) {
                bestScore = ds; bestPaths = dp;
            }
        }

        t[i][j] = {bestScore, bestPaths % MOD};
        return t[i][j];
    }

public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        n = board.size();
        t.assign(n, vector<pair<int, int>>(n, {-1, -1}));
        pair<int, int> ans = solve(n - 1, n - 1, board);
        return {ans.first, ans.second};
    }
};