class Solution {
 public:
  int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
    int n = books.size();

    // dp[i] = minimum height required for first i books
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
      int width = 0;
      int height = 0;

      // Try placing books j...i on the last shelf
      for (int j = i; j >= 1; j--) {
        width += books[j - 1][0];

        // Shelf is full
        if (width > shelfWidth) break;

        // Maximum height on the current shelf
        height = max(height, books[j - 1][1]);

        // Books 1...(j-1) are already optimally placed
        dp[i] = min(dp[i], dp[j - 1] + height);
      }
    }

    return dp[n];
  }
};