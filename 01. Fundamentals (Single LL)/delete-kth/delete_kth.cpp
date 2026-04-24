/*
Definition of singly linked list:
class ListNode{
  public:
    int data;
    ListNode *next;
    ListNode() : data(0), next(nullptr) {}
    ListNode(int x) : data(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : data(x), next(next) {}
};
*/

class Solution {
public:
    ListNode* deleteKthNode(ListNode* &head, int k) {
        if (!head) return head;
        if (k == 1) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }

        ListNode* current = head;
        ListNode* prev = head;

        for (int i = 1; i < k && current != NULL; i++) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) return head;
        prev->next = current->next;
        delete current;
        return head;
    }
};
