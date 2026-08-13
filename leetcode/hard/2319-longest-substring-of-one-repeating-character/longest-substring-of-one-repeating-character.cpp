struct Node {
  char lc, rc;
  int len;
  int pref;
  int suff;
  int best;
};
class Tree {
  vector<Node> segTree;
  string s;
  int n;

 public:
  Tree(string s) {
    this->s = s;
    n = s.size();
    segTree.resize(4 * n);
    build(0, 0, n - 1);
  }
  Node merge(Node l, Node r) {
    Node cur;
    cur.lc = l.lc;
    cur.rc = r.rc;
    cur.len = l.len + r.len;
    cur.pref = l.pref;
    if (l.pref == l.len && l.rc == r.lc) {
      cur.pref += r.pref;
    }
    cur.suff = r.suff;
    if (r.suff == r.len && l.rc == r.lc) {
      cur.suff += l.suff;
    }
    cur.best = max(l.best, r.best);
    if (l.rc == r.lc) {
      cur.best = max(cur.best, l.suff + r.pref);
    }
    return cur;
  }
  void build(int i, int l, int r) {
    if (l == r) {
      segTree[i] = {s[l], s[l], 1, 1, 1, 1};
      return;
    }
    int mid = l + (r - l) / 2;
    build(2 * i + 1, l, mid);
    build(2 * i + 2, mid + 1, r);
    segTree[i] = merge(segTree[2 * i + 1], segTree[2 * i + 2]);
  }
  void update(int i, int l, int r, int idx, char ch) {
    if (l == r) {
      segTree[i] = {ch, ch, 1, 1, 1, 1};
      return;
    }
    int mid = l + (r - l) / 2;
    if (idx <= mid) {
      update(2 * i + 1, l, mid, idx, ch);
    } else {
      update(2 * i + 2, mid + 1, r, idx, ch);
    }
    segTree[i] = merge(segTree[2 * i + 1], segTree[2 * i + 2]);
  }
  int query() { return segTree[0].best; }
};
class Solution {
 public:
  vector<int> longestRepeating(string s, string queryCharacters,
                               vector<int>& queryIndices) {
    Tree st(s);
    vector<int> ans;
    int n = s.size();
    int k = queryCharacters.size();
    for (int i = 0; i < k; i++) {
      st.update(0, 0, n - 1, queryIndices[i], queryCharacters[i]);
      ans.push_back(st.query());
    }
    return ans;
  }
};