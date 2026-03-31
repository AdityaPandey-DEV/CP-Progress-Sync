class Solution {
 public:
  string generateString(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();
    int len = n + m - 1;
    vector<bool> canChange(len, false);
    string str(len, '#');
    int i = 0;
    while (i < n) {
      if (str1[i] == 'T') {
        int j = 0;
        while (j < m) {
          if (str[i + j] == '#' || str[i + j] == str2[j]) {
            str[i + j] = str2[j];
          } else {
            return "";
          }

          j++;
        }
      }
      i++;
    }
    for (int i = 0; i < len; i++) {
      if (str[i] == '#') {
        canChange[i] = true;
        str[i] = 'a';
      }
    }
    i = 0;
    while (i < n) {
      if (str1[i] == 'F') {
        int j = 0;
        bool match = true;
        while (j < m) {
          if (str[i + j] != str2[j]) {
            match = false;

            break;
          }

          j++;
        }
        if (match) {
          bool changed = false;
          for (int j = m - 1; j >= 0; j--) {
            if (canChange[i + j]) {
              for (auto ch = 'a'; ch <= 'z'; ch++) {
                if (ch != str2[j]) {
                  str[i + j] = ch;
                  changed = true;
                  break;
                }
              }
            }
            if (changed) break;
          }
          if (!changed) return "";
        }
      }
      i++;
    }
    return str;
  }
};