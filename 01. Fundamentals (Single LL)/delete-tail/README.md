# Deletion of the Tail of LL

## Problem

Given the `head` of a singly linked list, delete the tail node and return the head of the modified list. The tail is the last node — the one whose `next` is `NULL`.

```
Input:  1 -> 2 -> 3
Output: 1 -> 2

Input:  1
Output: [] (head becomes NULL)
```

---

## Approach

Deleting the tail is harder than deleting the head because a singly linked list has no back-pointers. To free the tail, we must also update its **predecessor's** `next` to `NULL`. That means we have to walk the list keeping track of *two* pointers: the current node and the node right before it.

There are three cases to handle:

1. **Empty list** (`!head`) → nothing to delete, return `NULL`.
2. **Single node** (`!head->next`) → the head *is* the tail. Delete it and return `NULL`. Without this special case, the main loop would leave `prev` stuck at `head` and then assign `head->next = NULL` while also deleting `head` — a double-use bug.
3. **Two or more nodes** → walk `current` to the tail while `prev` trails one step behind, then unlink and free.

### Walk-through for `1 -> 2 -> 3`

```
initial:          prev=[1]  current=[1]
iter 1: current->next=[2] exists
        prev=[1]  current=[2]
iter 2: current->next=[3] exists
        prev=[2]  current=[3]
iter 3: current->next=NULL → exit loop

prev=[2]  current=[3]
prev->next = NULL       // [2] no longer points at [3]
delete current          // [3] freed
return head → [1] → [2] → NULL
```

---

## Code

```cpp
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
```

### Why two pointers

After the loop, `current` points to the tail — but `current` alone can't detach itself, because the node before it still holds a `next` pointer to it. We need `prev` to rewrite that link. In a doubly linked list we'd skip this dance and use `tail->prev->next = NULL`.

### Order of operations

`prev->next = NULL` **before** `delete current`. If you delete first and then touch `current` again, you're reading freed memory. Here it doesn't matter — we only use `prev`, not `current`, after the delete — but the habit of "unlink, then free" is worth keeping.

---

## Complexity

- **Time:** `O(n)` — we walk the entire list once to find the tail.
- **Space:** `O(1)` — two pointers, regardless of list size.
