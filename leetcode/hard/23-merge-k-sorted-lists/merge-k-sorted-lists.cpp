/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
  class Compare {
   public:
    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }
  };

 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
    int size = lists.size();
    for (int i = 0; i < size; i++) {
      ListNode* curr = lists[i];
      while (curr) {
        pq.push(curr);
        curr = curr->next;
      }
    }
    ListNode* root = new ListNode();
    ListNode* curr = root;
    while (!pq.empty()) {
      ListNode* s = pq.top();
      curr->next = s;
      pq.pop();
      curr = curr->next;
    }
    curr->next = NULL;
    return root->next;
  }
};