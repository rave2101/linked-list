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
    ListNode* insertAtKthPosition(ListNode* &head, int X, int K) {
        ListNode* newNode = new ListNode(X);
        if (!head) {
            return (K == 1) ? newNode : NULL;
        }

        if (K == 1) {
            newNode->next = head;
            return newNode;
        }
        ListNode* current = head;
        ListNode* prev = head;
        for (int i = 1; (i < K && current); i++) {
            prev = current;
            current = current->next;
        }
        newNode->next = current;
        prev->next = newNode;
        return head;
    }
};
