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
    ListNode* deleteHead(ListNode* &head) {
        if (!head) return NULL;
        ListNode* current = head->next;
        delete head;
        return current;
    }
};
