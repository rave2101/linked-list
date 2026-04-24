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
    vector<int> LLTraversal(ListNode *head) {
        if (!head) return {};
        vector<int> result;
        ListNode *ptr = head;
        while (ptr) {
            result.push_back(ptr->data);
            ptr = ptr->next;
        }
        return result;
    }
};
