class Solution {
  vector<vector<string>> ans;
  vector<string> board;
  int n;
  bool check(int i, int j) {
    for (int k = 0; k < n; k++) {
      if (board[i][k] == 'Q' || board[k][j] == 'Q') return false;
    }
    for (int r = i - 1, c = j - 1; r >= 0 && c >= 0; r--, c--) {
      if (board[r][c] == 'Q') {
        return false;
      }
    }
    for (int r = i - 1, c = j + 1; r >= 0 && c < n; r--, c++) {
      if (board[r][c] == 'Q') {
        return false;
      }
    }
    return true;
  }
  void rec(int i) {
    if (i == n) {
      ans.push_back(board);
      return;
    }
    for (int j = 0; j < n; j++) {
      if (check(i, j)) {
        board[i][j] = 'Q';
        rec(i + 1);
        board[i][j] = '.';
      }
    }
  }

 public:
  vector<vector<string>> solveNQueens(int n) {
    this->n = n;
    board.assign(n, string(n, '.'));
    rec(0);
    return ans;
  }
};