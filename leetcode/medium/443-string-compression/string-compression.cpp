class Solution {
 public:
  int compress(vector<char>& chars) {
    int i = 0, idx = 0, count = 0;

    int n = chars.size();
    while (i < n) {
      char currChar = chars[i];
      while (i < n && chars[i] == currChar) {
        count++;
        i++;
      }
      chars[idx++] = currChar;
      int j = 0;
      if (count > 1) {
        string sno = to_string(count);
        while (j < sno.size()) {
          chars[idx] = sno[j];
          j++;
          idx++;
        }
      }
      count = 0;
    }
    return idx;
  }
};