class Solution {
 public:
  vector<int> survivedRobotsHealths(vector<int>& positions,
                                    vector<int>& healths, string directions) {
    int n = positions.size();
    vector<int> ai(n);
    for (int i = 0; i < n; i++) {
      ai[i] = i;
    }
    auto lamda = [&](int& i, int& j) { return positions[i] < positions[j]; };
    sort(ai.begin(), ai.end(), lamda);
    vector<int> result;
    stack<int> st;
    for (auto curr : ai) {
      if (directions[curr] == 'R') {
        st.push(curr);
      } else {
        while (!st.empty() && healths[curr] > 0) {
          int top = st.top();
          st.pop();
          if (healths[top] > healths[curr]) {
            healths[top] -= 1;
            healths[curr] = 0;
            st.push(top);
          } else if (healths[top] < healths[curr]) {
            healths[top] = 0;
            healths[curr] -= 1;
          } else {
            healths[top] = 0;
            healths[curr] = 0;
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (healths[i] > 0) {
        result.push_back(healths[i]);
      }
    }
    return result;
  }
};