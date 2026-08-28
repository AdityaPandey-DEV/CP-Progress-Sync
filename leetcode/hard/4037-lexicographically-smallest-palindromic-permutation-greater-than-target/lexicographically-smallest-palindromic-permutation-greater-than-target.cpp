class Solution {
  int n;
  string target;
  string ans;
  map<char, int> mp;
  char mid;
  bool isOk(string s) {
    for (auto &ch : s) {
      mp[ch]++;
    }
    int cnt = 0;
    for (auto &p : mp) {
      if (p.second % 2 != 0) {
        ans[n / 2] = p.first;
        mp[p.first]--;
        // cout<<ans[n/2]<<endl;
        mid = p.first;
        // cout<<ans[n/2]<<" "<<target[n/2]<<endl;
        cnt++;
      }
    }
    return cnt < 2;
  }
  bool rec(int i, bool greater) {
    if (i == n / 2) {
      if (mid != '0') {
        ans[i] = mid;
      }
      return ans > target;
    };
    // cout<<i<<" "<<greater<<endl;
    // cout<<"start :-"<<i<<" "<<ans[n/2]<<endl;
    char ch = target[i];
    if (mp.find(ch) != mp.end() && mp[ch] >= 2 && !greater) {
      mp[ch] -= 2;
      ans[i] = ch;
      ans[n - i - 1] = ch;
      // cout<<i<<" "<<ans[i]<<n-i-1<<" "<<ans[n-i-1]<<endl;
      if (rec(i + 1, false)) return true;
      mp[ch] += 2;
    }
    char c = target[i];
    for (auto &p : mp) {
      if ((!greater && p.first <= c) || (mp[p.first] < 2)) continue;
      mp[p.first] -= 2;
      ans[i] = p.first;
      ans[n - i - 1] = p.first;
      // cout<<i<<" "<<ans[i]<<n-i-1<<" "<<ans[n-i-1]<<endl;
      bool nextGreater = greater || p.first > c;
      if (rec(i + 1, nextGreater)) return true;
      mp[p.first] += 2;
    }
    // cout<<"end:-"<<i<<" "<<ans[n/2]<<endl;
    return false;
  }

 public:
  string lexPalindromicPermutation(string s, string target) {
    mid = '0';
    ans = s;
    n = s.size();
    this->target = target;
    bool ok = isOk(s);
    // cout<<"1:"<<endl;
    if (!ok) return "";
    // cout<<"2:"<<endl;
    if (n <= 2) {
      if (s > target && ok) return s;
      return "";
    }
    // cout<<"3:"<<endl;
    // cout<<g<<endl;

    if (rec(0, false)) return ans;
    // cout<<"4:"<<endl;
    return "";
  }
};