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
    ListNode* insertBeforeX(ListNode* &head, int X, int val) {
        ListNode* newNode = new ListNode(val);
        if (head->data == X) {
            newNode->next = head;
            return newNode;
        }
        ListNode* current = head;
        ListNode* prev = head;

        while (current && current->data != X) {
            prev = current;
            current = current->next;
        }
        if (!current) return head;

        newNode->next = current;
        prev->next = newNode;
        return head;
    }
};
