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
  ListNode* findMid(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  }
  ListNode* reverse(ListNode* head) {
    ListNode* curr = head;
    ListNode* prev = NULL;
    ListNode* next = NULL;

    while (curr != NULL) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }

 public:
  int pairSum(ListNode* head) {
    ListNode* curr = head;
    ListNode* mid = findMid(head);
    ListNode* tail = reverse(mid);
    int sum = 0;
    int maxSum = 0;
    while (tail != NULL) {
      sum = curr->val + tail->val;
      maxSum = max(sum, maxSum);
      curr = curr->next;
      tail = tail->next;
    }
    return maxSum;
  }
};