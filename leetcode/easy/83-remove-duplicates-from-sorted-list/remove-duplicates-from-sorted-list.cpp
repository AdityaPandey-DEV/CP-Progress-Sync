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
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    set<int> st;
    if (head == NULL) {
      return NULL;
    }
    ListNode* curr = head;
    st.insert(curr->val);
    while (curr->next != NULL) {
      if (st.count(curr->next->val)) {
        curr->next = curr->next->next;
      } else {
        st.insert(curr->next->val);
        curr = curr->next;
      }
    }
    return head;
  }
};