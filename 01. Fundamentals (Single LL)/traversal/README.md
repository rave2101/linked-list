# Traversal in Linked List

## Problem

Given the `head` of a singly linked list, traverse the entire list and return its elements in an array, in the order they appear.

```
Input:  5 -> 4 -> 3 -> 1 -> 0
Output: [5, 4, 3, 1, 0]

Input:  1
Output: [1]
```

---

## Approach

A linked list only exposes one entry point — `head`. Each node knows the address of the next node via its `next` pointer. The last node's `next` is `nullptr`, which is our stop signal.

So traversal is the simplest possible loop:

1. Start a walker pointer `ptr` at `head`.
2. While `ptr` is not null, append `ptr->data` to the result and advance `ptr = ptr->next`.
3. Return the result.

We don't mutate `head`; we use a separate pointer `ptr` so the caller's handle to the list is preserved.

### Walk-through for `5 -> 4 -> 3 -> 1 -> 0`

```
ptr = head(5)   result = [5]          ptr = ptr->next → 4
ptr = 4         result = [5,4]        ptr = ptr->next → 3
ptr = 3         result = [5,4,3]      ptr = ptr->next → 1
ptr = 1         result = [5,4,3,1]    ptr = ptr->next → 0
ptr = 0         result = [5,4,3,1,0]  ptr = ptr->next → nullptr
ptr = nullptr   loop exits
```

---

## Code

```cpp
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
```

The `if (!head) return {};` guard is not strictly necessary — the `while (ptr)` loop already handles an empty list by never entering. It's kept as an explicit early exit.

---

## Complexity

- **Time:** `O(n)` — each node is visited once.
- **Space:** `O(n)` for the output array. Traversal itself uses `O(1)` extra space (one pointer).
