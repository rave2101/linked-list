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
    ListNode* deleteTail(ListNode* &head) {
        if (!head) return NULL;
        if (!head->next) {
            delete head;
            return NULL;
        }
        ListNode* prev = head;
        ListNode* current = head;
        while (current->next) {
            prev = current;
            current = current->next;
        }
        prev->next = NULL;
        delete current;
        return head;
    }
};
