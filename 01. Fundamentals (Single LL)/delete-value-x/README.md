# Delete the Element with Value X

## Problem

Given the `head` of a singly linked list and an integer `X`, delete the **first** node whose value equals `X` and return the head of the modified list. If no node matches, return the list unchanged.

```
Input:  3 -> 4 -> 5,   X = 5
Output: 3 -> 4

Input:  3 -> 4 -> 5,   X = 7
Output: 3 -> 4 -> 5    (no match)
```

---

## Approach

This is the positional-delete problem with the search condition swapped from "am I at index `k`?" to "does my node's data equal `X`?". The structure is the same two-pointer walk, with two branches:

1. **Head matches** (`head->data == X`) — detach head, advance the caller's head pointer to the second node, free the old head. This is the same pattern as *delete-head*.
2. **Match somewhere inside** — walk `current` forward with `prev` trailing. As soon as `current->data == X`, stitch `prev->next = current->next`, free `current`, return.
3. **No match** — the loop falls off the end with `current == NULL`. Return the list untouched.

Note the "first match" semantics: the moment we find `X` we `return`, so if `X` appears multiple times only the earliest occurrence is removed.

### Walk-through for `3 -> 4 -> 5`, X = 5

```
head->data=3 ≠ 5 → skip head branch

prev=[3]  current=[3]
  current->data=3 ≠ 5 → advance. prev=[3]  current=[4]
  current->data=4 ≠ 5 → advance. prev=[4]  current=[5]
  current->data=5 == 5 → match
    prev->next = current->next  // [4]->next becomes NULL
    delete current              // free [5]
    return head

result: 3 -> 4 -> NULL
```

---

## Code

```cpp
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
```

### `prev` only advances on non-match

In the search loop, `prev = current` happens in the `else` branch — only when the current node survives. If we had advanced `prev` unconditionally (like in the kth-delete loop), `prev` would sometimes land on the node we just freed. Doing it this way keeps `prev` at the last *surviving* node, which is exactly the predecessor we need for the stitch.

### Missing empty-list guard

This solution dereferences `head->data` before checking `head != NULL`. If the judge ever calls it with an empty list, it crashes. An interviewer-safe version would start with `if (!head) return NULL;`. The passing submission gets away with it because the test cases always have at least one node.

---

## Complexity

- **Time:** `O(n)` — in the worst case (no match, or match at the tail) we scan the whole list.
- **Space:** `O(1)` — two pointers.
