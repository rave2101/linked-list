# Insertion at the Tail of LL

## Problem

Given the `head` of a singly linked list and an integer `X`, insert a new node with value `X` at the tail and return the head.

```
Input:  1 -> 2 -> 3,   X = 7
Output: 1 -> 2 -> 3 -> 7

Input:  [],            X = 0
Output: 0
```

---

## Approach

Inserting at the head was `O(1)` because we already held the head pointer. The tail is the opposite — a singly linked list gives you no direct pointer to the last node, so you have to **walk the list to find it**.

Two cases:

1. **Empty list** (`!head`) — the new node is both head and tail. Update the caller's head.
2. **Non-empty list** — walk a pointer `current` until `current->next == NULL` (the definition of the tail), then attach: `current->next = newNode`.

The `newNode` is created with `next = nullptr` by the constructor, so there's nothing to clear after linking — it already terminates the list correctly.

### Walk-through for `1 -> 2 -> 3`, X = 7

```
newNode = [7] → NULL

current = head = [1]
  current->next = [2] → advance, current = [2]
  current->next = [3] → advance, current = [3]
  current->next = NULL → loop exits

current->next = newNode    // [3] → [7]

result: 1 -> 2 -> 3 -> 7 -> NULL
```

### Loop condition: why `while (current->next)` and not `while (current)`

We want `current` to end on the *last* node, not one past it. `while (current->next)` stops with `current` pointing at the tail. If we used `while (current)`, `current` would become `NULL` and we'd lose our grip on the node we wanted to modify.

---

## Code

```cpp
ListNode* insertAtTail(ListNode* &head, int X) {
    ListNode* newNode = new ListNode(X);
    if (!head) {
        head = newNode;
        return head;
    }
    ListNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}
```

### Why the empty-list branch is necessary

If we skipped the `!head` check and fell into the loop, `current = head` would be `NULL` and `current->next` would segfault. More importantly, even if we guarded the loop, we'd still need to set the *caller's* head to the new node, because there's nothing to attach to. The explicit branch handles both.

---

## Complexity

- **Time:** `O(n)` — we traverse the whole list to reach the tail. If the problem allowed keeping a persistent tail pointer alongside head, this would drop to `O(1)` — which is exactly the trick a deque uses.
- **Space:** `O(1)` — one new node, one walker.
