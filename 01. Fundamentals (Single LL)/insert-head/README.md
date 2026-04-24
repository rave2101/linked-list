# Insertion at the Head of LL

## Problem

Given the `head` of a singly linked list and an integer `X`, insert a new node with value `X` at the head and return the new head.

```
Input:  1 -> 2 -> 3,   X = 7
Output: 7 -> 1 -> 2 -> 3

Input:  [],            X = 7
Output: 7
```

---

## Approach

A new head has to do two things:
1. Know where the *old* list starts — so its `next` must point to the current head.
2. Become the *new* entry point — so the caller's `head` must update to point at it.

Do them in that order: wire first, then reseat the head. If you reseated `head` first and then tried to set `head->next` to the old head, you've already lost the old head's address.

### Walk-through for `1 -> 2 -> 3`, X = 7

```
before:   head → [1] → [2] → [3] → NULL

step 1:   current = new ListNode(7)       // [7] → NULL (dangling)
step 2:   current->next = head            // [7] → [1] → [2] → [3]
step 3:   head = current                  // head now points to [7]

after:    head → [7] → [1] → [2] → [3] → NULL
```

### Empty-list case

If `head` is `NULL`, step 2 sets `current->next = NULL` (which `new ListNode(7)` already did), and step 3 makes the new node the only node. No special-casing needed — the general code handles it.

---

## Code

```cpp
ListNode* insertAtHead(ListNode* &head, int X) {
    ListNode* current = new ListNode(X);
    current->next = head;
    head = current;
    return head;
}
```

### Why `head` is a reference

`ListNode* &head` lets us mutate the caller's pointer directly — after the call, the caller's variable already points at the new head. The `return head` is redundant with the reference, but harmless; either mechanism alone would be enough.

---

## Complexity

- **Time:** `O(1)` — no traversal, just a few pointer writes.
- **Space:** `O(1)` — a single new node.
