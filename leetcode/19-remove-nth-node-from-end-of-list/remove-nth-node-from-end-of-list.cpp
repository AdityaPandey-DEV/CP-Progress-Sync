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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int size=0;
        ListNode* curr=head;
        while(curr){
            curr=curr->next;
            size++;
        }
        int idx=size-n-1;
        curr=head;
        if(size==n){
            return head->next;
        }
        while(idx){
            curr=curr->next;
            idx--;
        }
        curr->next=curr->next->next;
        return head;

    }
};