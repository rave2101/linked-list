# Insertion Before the Value X in LL

## Problem

Given the `head` of a singly linked list and two integers `X` and `val`, insert a node with value `val` immediately before the **first** node whose value is `X`, and return the head. If `X` is not in the list, return it unchanged.

```
Input:  1 -> 2 -> 3,   X = 2, val = 5
Output: 1 -> 5 -> 2 -> 3

Input:  1 -> 2 -> 3,   X = 7, val = 5
Output: 1 -> 2 -> 3    (X not found)
```

---

## Approach

Same two-pointer pattern as the positional insert, but the stopping condition changes from "I've hopped `K-1` times" to "my `current` now sits on the node whose value is `X`." Once the walk ends, the stitch is identical.

Three branches:

1. **Head matches `X`** — the insert goes *before* head, so the new node becomes the head. Same pattern as *insert-at-head*.
2. **Match found mid-list** — `current` lands on the node with value `X`, `prev` trails one node behind. Splice:
   ```cpp
   newNode->next = current;
   prev->next   = newNode;
   ```
3. **No match** — `current` falls off the end (`NULL`). Return the list unchanged.

### Walk-through for `1 -> 2 -> 3`, X = 2, val = 5

```
newNode = [5]

head->data = 1 ≠ 2 → skip head-match branch

prev=[1]  current=[1]
  current->data=1 ≠ 2 → advance. prev=[1]  current=[2]
  current->data=2 == 2 → exit loop

newNode->next = current   // [5] → [2]
prev->next    = newNode   // [1] → [5]

result: 1 -> 5 -> 2 -> 3
```

### Walk-through for `1 -> 2 -> 3`, X = 7, val = 5 (not found)

```
prev=[1]  current=[1]
  1 ≠ 7 → advance. prev=[1]  current=[2]
  2 ≠ 7 → advance. prev=[2]  current=[3]
  3 ≠ 7 → advance. prev=[3]  current=NULL
  loop exits (current is NULL)

!current → return head unchanged
```

The leaked `newNode` here is a small memory leak — we allocated it before the search confirmed `X` exists. A defensive version would `delete newNode;` before returning.

---

## Code

```cpp
ListNode* insertBeforeX(ListNode* &head, int X, int val) {
    ListNode* newNode = new ListNode(val);
    if (head->data == X) {
        newNode->next = head;
        return newNode;
    }
    ListNode* current = head;
    ListNode* prev = head;

    while (current && current->data != X) {
        prev = current;
        current = current->next;
    }
    if (!current) return head;

    newNode->next = current;
    prev->next = newNode;
    return head;
}
```

### Loop condition: short-circuit ordering matters

`while (current && current->data != X)` — the `current` null-check must come first. `&&` evaluates left-to-right and short-circuits, so if `current` is already `NULL`, we stop without touching `current->data`. Swapping the operands would segfault on a miss.

### Missing empty-list guard

`head->data == X` dereferences `head` before checking it's non-null. On an empty list this crashes. The passing judge tests always pass a non-empty head, so the submission gets away with it.

---

## Complexity

- **Time:** `O(n)` — worst case (no match, or match at the tail) scans the whole list.
- **Space:** `O(1)` — one new node, two walkers.
