class Solution {
    vector<int> noOfOne, noOfZero;
    int rec(int l, int r) {
    if (l >= r) return 1e8;
    
    int len = r - l + 1;
    int one = noOfOne[r] - (l != 0 ? noOfOne[l - 1] : 0);
    int zero = noOfZero[r] - (l != 0 ? noOfZero[l - 1] : 0);
    int ans = min(one, zero);

    if (len > 2) {
        int mid = l + (r - l) / 2;
        // Adjust mid so the left half [l, mid] always has even length
        if ((mid - l + 1) % 2 != 0) {
            mid--; 
        }
        ans = min(ans, rec(l, mid) + rec(mid + 1, r));
    }
    return ans;
}

public:
    int minChanges(string s) {
        int n = s.size();
        noOfOne.resize(n);
        noOfZero.resize(n);
        // preprocess noOfOne and noOfZero
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                noOfZero[i] += noOfZero[i - 1];
                noOfOne[i] += noOfOne[i - 1];
            }
            if (s[i] == '0') {
                noOfZero[i]++;
            } else {
                noOfOne[i]++;
            }

            // cout<<"zero:-"<<noOfZero[i]<<"one:-"<<noOfOne[i]<<endl;
        }
        int l = 0, r = n - 1;
        return rec(l, r);
    }
};