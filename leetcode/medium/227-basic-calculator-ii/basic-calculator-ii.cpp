class Solution {
 public:
  int calculate(string s) {
    int currNo = 0;
    int n = s.size();
    char op = '+';
    stack<int> st;
    for (int i = 0; i < n; i++) {
      char currChar = s[i];
      if (isdigit(currChar)) {
        currNo *= 10;
        currNo += currChar - '0';
      }
      if (!isdigit(currChar) && !isspace(currChar) || i == n - 1) {
        if (op == '-') {
          st.push(-currNo);
        } else if (op == '+') {
          st.push(currNo);
        } else if (op == '*') {
          int top = st.top();
          st.pop();

          st.push(currNo * top);
        } else if (op == '/') {
          int top = st.top();
          st.pop();
          st.push(top / currNo);
        }
        op = currChar;
        currNo = 0;
      }
    }
    int ans = 0;
    while (!st.empty()) {
      ans += st.top();
      st.pop();
    }
    return ans;
  }
};