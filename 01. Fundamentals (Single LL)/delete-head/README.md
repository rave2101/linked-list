# Deletion of the Head of LL

## Problem

Given the `head` of a singly linked list, delete the head node and return the head of the modified list.

```
Input:  1 -> 2 -> 3
Output: 2 -> 3
```

If the list is empty, return `NULL`.

---

## Approach

The head node owns two things: its data, and a pointer to the next node. To remove it cleanly we need to:

1. **Remember the second node** before we destroy the first — otherwise we lose the rest of the list.
2. **Free the old head's memory** with `delete` so we don't leak.
3. **Return the second node** as the new head.

Order matters. If you `delete head` first and *then* try to read `head->next`, you're dereferencing freed memory (undefined behavior). So we read `head->next` into a temporary first.

### Walk-through for `1 -> 2 -> 3`

```
before:   head → [1] → [2] → [3] → NULL

step 1:   current = head->next       // current → [2]
step 2:   delete head                // frees the [1] node
step 3:   return current             // caller's head is now [2]

after:    head → [2] → [3] → NULL
```

---

## Code

```cpp
ListNode* deleteHead(ListNode* &head) {
    if (!head) return NULL;
    ListNode* current = head->next;
    delete head;
    return current;
}
```

### Why `ListNode* &head` (reference to pointer)

The signature passes `head` by reference, but this function doesn't actually need to modify the caller's pointer — it returns the new head instead. The reference is harmless here; the caller uses the return value.

### Why `delete head`

The node was created with `new` somewhere upstream. Without `delete`, the node's memory is leaked — still allocated but unreachable. In an interview, always free the node you detach.

---

## Complexity

- **Time:** `O(1)` — constant number of pointer operations.
- **Space:** `O(1)` — one temporary pointer.
