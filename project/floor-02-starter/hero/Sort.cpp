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
#include <sstream>

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

    Comparator makeComparator(const std::string& key, bool descending) {
        Comparator cmp;
        if (key == "name") {
		    cmp = [](const Item& a, const Item& b) {
                return a.name < b.name;
            };
        }
        else if (key == "weight") {
            cmp = [](const Item& a, const Item& b) {
                return a.weight < b.weight;
            };
        }
        else if (key == "value") {
            cmp = [](const Item& a, const Item& b) {
                return a.value < b.value;
            };
        }
        else {
            return nullptr;
	    }
        if (descending) {
            Comparator asc = cmp;
            cmp = [asc](const Item& a, const Item& b) {
                return asc(b, a);
	        };
        }
		return cmp;
    }

    bool sortInventory(Hero& hero, const std::string& criterion) {
		std::istringstream in(criterion);
        std::string key;
        std::string dir;
		in >> key >> dir;

        bool descending = (dir == "desc");
        Comparator cmp = makeComparator(key, descending);
        if (!cmp) {
            return false;
        }
		mergeSort(hero.inventory, cmp);
		return true;
    }

}  // namespace dungeon
