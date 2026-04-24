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
    ListNode* deleteNodeWithValueX(ListNode* &head, int X) {
        if (head->data == X) {
            ListNode* current = head;
            head = head->next;
            delete current;
            return head;
        }
        ListNode* current = head;
        ListNode* prev = head;
        while (current) {
            if (current->data == X) {
                prev->next = current->next;
                delete current;
                return head;
            } else {
                prev = current;
                current = current->next;
            }
        }
        return head;
    }
};
