# Trial I — *The Foundations Brief*

*Warden of the Foundations · Midterm 1 · 15 %*

Four short answers, one from each floor above. **50–100 words per answer.** No code on this trial (except the lambdas in Q3); just clear thinking.

AI is welcome to *check* your answers; it is not welcome to *write your sentences*. These answers are short enough that an LLM voice is recognisable.

---

## 1. Floor 0 — ADT

> Your battle's "Use item" menu shows the *currently usable* items in your hero's inventory on this turn. Name the right ADT for that menu. Defend the choice against its closest neighbour (e.g., why `bag` instead of `set`, or `list` instead of `bag`).

The ADT I would choose for this is the bag. The hero's inventory is already stored in a bag to allow duplicates, unlike a set. In a list, the order is important, whereas for this all we need to do is pick any item no matter where.

---

## 2. Floor 1 — search & Big-O

> Your inventory is kept sorted by healing power (in this codebase an item's `value` measures its potency, so `value` plays the healing-power role). The player types `use Healing potion`. Linear or binary search to find it by name? Justify, and give the Big-O for each.

Binary would be better here since my inventory is sorted. Because it is sorted, Binary would have a big-O of O(log n) while linear would have a big-O of O(n). Even with the search being by name, the computer knows the value of each name and the list is sorted by the value. This is similar to the challenge on paper we had at the start of class. Each binary sort splits the list to check in 2 rather than go through every single item, which as we progress through the game and gain more loot becomes crucial to not slowing down the game rate.

---

## 3. Floor 2 — sort & comparators

> Your "Use item" menu must be displayable sorted *either* by healing power (meaning `value`) *or* by weight. Show a one-line comparator (lambda) for each. One sentence on what language feature makes one `std::sort` call serve both orders.

*Note: `Item` has no healing field — an item's `value` measures its potency, so `value` plays the healing-power role here and in your battle.*

```cpp
// by healing power — i.e. by value
auto byValue = [](const Item& a, const Item& b) { return a.value < b.value; };

// by weight
auto byWeight = [](const Item& a, const Item& b) {return a.weight < b.weight; };
```

The language feature that makes one `std::sort` call serve both orders is the comparator/lambda because it allows the sort to be told how to sort stuff and it just sorts it.

---

## 4. Floor 3 — templates & exceptions

> Why does `Bag<T>` live in `Bag.h` instead of `Bag.cpp`? And: when the player types `9` for a 4-option menu, where in your code should the validation **throw**, and where should it **catch**?

Bag<T> lives in 'Bag.h' instead of 'Bag.cpp' because templates must be defined in the same file otherwise it would only compile for the types that are named in the .cpp file. When the player types `9` for a 4-option menu, within the try in main the .at() within the Bag<T> should throw and be caught in main by catch, allowing the game to continue.
