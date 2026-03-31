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
    void reorderList(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast->next&&fast->next->next){
            fast=fast->next->next;
            slow=slow->next;

        }
        ListNode*prev=NULL;
        ListNode*curr=slow->next;
        slow->next=NULL;
        while(curr!=NULL){
            ListNode* next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        ListNode* first=head;
        ListNode* second=prev;
        while(second){
            ListNode* fnext=first->next;
            ListNode* snext=second->next;
            first->next=second;
            second->next=fnext;
            first=fnext;
            second=snext;
            

        }
        
        
    }
};