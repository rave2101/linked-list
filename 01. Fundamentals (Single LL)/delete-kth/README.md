# Deletion of the Kth Node of LL

## Problem

Given the `head` of a singly linked list and a 1-indexed position `k`, delete the kth node and return the head of the modified list.

```
Input:  3 -> 4 -> 5,   k = 2
Output: 3 -> 5

Input:  1 -> 2 -> 3,   k = 1
Output: 2 -> 3         (head changed)
```

If `k` is larger than the list length, return the list unchanged.

---

## Approach

Generalising the two earlier problems:
- **`k = 1`** is *delete-head* — the caller's starting pointer becomes a different node, so we must return the new head.
- **`k > 1`** requires walking two pointers (`prev` and `current`) until `current` sits on the kth node, then stitching `prev->next = current->next` and freeing `current`.

We also have to defend against **`k` out of range**. If the list has fewer than `k` nodes, the walk falls off the end (`current` becomes `NULL`). The loop's `current != NULL` guard stops us before we dereference a null pointer; after the loop we check and return the list untouched.

### The loop's two-condition guard

```cpp
for (int i = 1; i < k && current != NULL; i++) {
    prev = current;
    current = current->next;
}
```

- `i < k` controls how many hops we want: starting at node 1, we need `k-1` hops to land on node `k`.
- `current != NULL` short-circuits before the body can execute `current->next` on a null pointer. Without it, calling this with `k = 100` on a 3-node list would crash instead of returning gracefully.

### Walk-through for `3 -> 4 -> 5`, k = 2

```
initial:           prev=[3]  current=[3]   i=1
iter (1<2, curr≠∅): prev=[3]  current=[4]   i=2 → exit

current=[4]  (the kth node)
prev->next = current->next   // [3]->next becomes [5]
delete current               // free [4]
return head → 3 -> 5
```

### Walk-through for `3 -> 4 -> 5`, k = 10 (out of range)

```
i=1: prev=[3]  current=[4]
i=2: prev=[4]  current=[5]
i=3: prev=[5]  current=NULL   ← current->next was NULL
i=4: current==NULL → exit loop

current == NULL → return head unchanged
```

---

## Code

```cpp
ListNode* deleteKthNode(ListNode* &head, int k) {
    if (!head) return head;
    if (k == 1) {
        ListNode* newHead = head->next;
        delete head;
        return newHead;
    }

    ListNode* current = head;
    ListNode* prev = head;

    for (int i = 1; i < k && current != NULL; i++) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return head;
    prev->next = current->next;
    delete current;
    return head;
}
```

### Why `k = 1` is handled separately

If we tried to reuse the main loop for `k = 1`, it would execute zero iterations (since `i = 1 < 1` is false). `prev` and `current` would both still point at `head`, and `prev->next = current->next` would make `head->next = head->next` — a no-op — followed by `delete current` which frees the head while the caller still holds a stale pointer to it. Splitting it out avoids the whole mess.

### Works for the tail too

When `k` equals the list length, `current` lands on the last node, `current->next` is `NULL`, and `prev->next = NULL` correctly terminates the list — so this subsumes the delete-tail case as a special instance.

---

## Complexity

- **Time:** `O(k)` — we stop as soon as we reach the kth node (or the end, if `k` is out of range). Worst case `O(n)`.
- **Space:** `O(1)` — two pointers.
