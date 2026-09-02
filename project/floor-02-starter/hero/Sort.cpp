// COMP 2450 — Floor 2 starter
// hero/Sort.cpp — YOU implement this file.
//
// Three functions to write. Read Sort.h for their contracts.
//
// The big idea this week: sorting is not one algorithm, it is a family
// of tradeoffs. Merge sort is predictable but copies. Quicksort is fast
// on average but betrays you on bad inputs. std::sort is what you
// actually ship. You will write the first two, race all three in
// `benchmark sort`, and argue — in a commit message — which one the
// game should call.
//
// Tips for the Pivot Wraith:
//   * If you pick the FIRST element as your quicksort pivot, a sorted
//     input becomes O(n^2). The `benchmark sort --bad-pivot --sorted`
//     harness exists to show you exactly that.
//   * The middle element is the cheapest defense. Good enough for this
//     week. Real production code (std::sort) does median-of-three and
//     switches algorithms on bad recursion depth.
//
// Submit when:  `sort inventory by weight` produces ascending weight,
//               `sort inventory by name desc` produces reverse alphabetical,
//               and `benchmark sort` gives three timing columns on every row.

#include "Sort.h"
#include <algorithm>  // you will want std::sort in sortInventory

namespace dungeon {

// ---- 1. Merge sort ------------------------------------------------------

    void Merge(std::vector<Item>& inventory, std::size_t lo, std::size_t mid, std::size_t hi, const Comparator& cmp) {
        std::vector<Item> scratch;
		scratch.reserve(hi - lo); // reserve space for the merged range
        std::size_t i = lo;
		std::size_t j = mid;

        while (i < mid && j < hi) {
            if (!cmp(inventory[j], inventory[i])) { // right does NOT precede left
                scratch.push_back(inventory[i]); // -> take the LEFT item
                i++;
            }
            else {
                scratch.push_back(inventory[j]); // -> take the RIGHT item
                j++;
            }
        }

        while (i < mid) { // whatever is left in the left half
            scratch.push_back(inventory[i]);
            i++;
        }
        while (j < hi) { // whatever is left in the right half
            scratch.push_back(inventory[j]);
            j++;
        }
        for (std::size_t k = 0; k < scratch.size(); ++k) { // write back over [lo, hi)
            inventory[lo + k] = scratch[k];
        }
    }

    void MergeSortImpl(std::vector<Item>& inventory, std::size_t lo, std::size_t hi, const Comparator& cmp) {
        if ((hi - lo) < 2) {
            return;
        }
        std::size_t mid = lo + (hi - lo) / 2;
        MergeSortImpl(inventory, lo, mid, cmp);
        MergeSortImpl(inventory, mid, hi, cmp);
        Merge(inventory, lo, mid, hi, cmp);
        return;
    }

void mergeSort(std::vector<Item>& inventory, const Comparator& cmp) {
    MergeSortImpl(inventory, 0, inventory.size(), cmp);
}

// ---- 2. Quicksort -------------------------------------------------------

std::size_t partition(std::vector<Item>& inventory, std::size_t lo, std::size_t hi, const Comparator& cmp) {
    std::size_t pivotIndex = lo + (hi - lo) / 2; // middle element as pivot
    std::swap(inventory[pivotIndex], inventory[hi]); // move pivot to the end
    const Item& pivot = inventory[hi];
    std::size_t store = lo;
    for (std::size_t j = lo; j < hi; ++j) {
        if (cmp(inventory[j], pivot)) { // if inventory[j] should come before pivot
            std::swap(inventory[store], inventory[j]);
            store++;
        }
    }
    std::swap(inventory[store], inventory[hi]); // move pivot to its final place
	return store; // return the index of the pivot
}

void quicksortImpl(std::vector<Item>& inventory, std::size_t lo, std::size_t hi, const Comparator& cmp) {
    if (lo < hi) {
        std::size_t p = partition(inventory, lo, hi, cmp);
        if (p > 0) {
            quicksortImpl(inventory, lo, p - 1, cmp);
        }
        quicksortImpl(inventory, p + 1, hi, cmp);
    }
}

void quicksort(std::vector<Item>& inventory, const Comparator& cmp) {
    if (!inventory.empty()) {
        quicksortImpl(inventory, 0, inventory.size() - 1, cmp);
    }
}

// ---- 3. sortInventory (the seam) ----------------------------------------

bool sortInventory(Hero& hero, const std::string& criterion) {
    // TODO Floor 2 (Fri): parse criterion, build the right comparator,
    // dispatch to a sort.
    //
    // Think before you type:
    //   - Three decisions to make: WHICH key, ASC or DESC, WHICH sort.
    //     Don't tangle them. Parse first, then build a comparator, then
    //     hand it to exactly one sort call.
    //   - Building a DESCENDING comparator from an ASCENDING one: you
    //     don't need a whole second comparator. Wrap the ascending one
    //     and swap its arguments. (Two-line lambda. Elegant.)
    //   - Which sort? std::sort wins on speed. Your mergeSort wins on
    //     stability (and it's YOUR code — the instructor hand-wrote
    //     std::sort's ancestor forty years ago and still refers to
    //     Sedgewick). Pick one. The *choice* is the assignment.
    //   - The "desc" case for `sort by weight`: does Iron key still come
    //     before Loaf of bread on ties? That answer tells you whether
    //     your chosen sort is stable — and whether stability is the
    //     right thing for this command. (Reasonable people disagree.)
    //
    // If you need structural hints — parse with std::istringstream:
    //
    //     std::istringstream in(criterion);
    //     std::string key, dir;
    //     in >> key >> dir;       // dir is "" if absent
    //
    // Build an ascending Comparator for each key ("name", "weight",
    // "value"). If dir == "desc", wrap it in a Comparator that swaps
    // the arguments of the ascending one.
    //
    // Return false on an unknown key (main.cpp will print an error).
    //
    // Dispatch: for this week std::sort is the right production choice.
    // Your mergeSort and quicksort are correct too — pick one and
    // defend it in your commit message.
    (void)hero;
    (void)criterion;
    return false;
}

}  // namespace dungeon
