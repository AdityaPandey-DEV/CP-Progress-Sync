class Solution {
public:
    int minInsertions(string s) {
        stack<char> st;
        int i = 0, n = s.size(), insert = 0;
        while (i < n) {
            cout<<i<<endl;
            if (s[i] == '(') {
                st.push(s[i]);
            }
            if (s[i] == ')') {
                if (st.empty()) {
                    cout << "st empty" << endl;
                    insert++;
                    
                } else {
                    
                    st.pop();
                }
                if (i + 1 < n && s[i + 1] == ')') {
                    i++;
                } else {
                    cout << "not" << endl;
                    insert++;
                }
            }
            i++;
        }
        insert+=(st.size()*2);
        return insert;
    }
};