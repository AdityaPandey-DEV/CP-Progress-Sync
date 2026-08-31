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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = NULL;
        int minDistance = 1e9, maxDistance = 0;
        int idx = -1;
        int i = 1;
        int sidx = -1;
        while (curr != NULL && curr->next != NULL) {
            if (prev != NULL &&
                ((curr->val > prev->val && curr->val > curr->next->val) ||
                 (curr->val < prev->val && curr->val < curr->next->val))) {
                if (idx == -1) {
                    idx = i;
                    sidx = i;
                } else {
                    minDistance = min(minDistance, i - idx);
                    idx = i;
                }
            }
            i++;
            prev = curr;
            curr = curr->next;
        }
        if (sidx != -1)
            maxDistance = idx - sidx;
        return {minDistance == 1e9 ? -1 : minDistance,
                maxDistance == 0 ? -1 : maxDistance};
    }
};