// COMP 2450 — Floor 1 starter
// bestiary/Search.cpp — YOU implement this file.
//
// Four functions to write. Read Search.h for their contracts.
//
// The big idea this week: the same question ("is X in the list?") has
// three implementations with three VERY different Big-O costs. You will
// write all three, race them in `benchmark`, and then argue — in a commit
// message — which one the rest of the game should use. The code is easy.
// The *thinking* is the point.
//
// Tips for the Unsorted Lich:
//   * binarySearch (and binarySearchRecursive) only work if the bestiary
//     is sorted by name.
//   * main.cpp already calls sortBestiary() right after loading,
//     so you can assume the precondition holds when these run.
//   * If you ever doubt, scan the vector and assert it is sorted.
//
// Submit when:  `search Goblin` returns the goblin's stats and `search Ghost`
//               reports "no such creature." Then run `benchmark` and capture
//               the output for your lab-notes.md.

#include "Search.h"

namespace dungeon {

    const Monster* linearSearch(const std::vector<Monster>& bestiary,
        const std::string& name) {
        for (const auto& m : bestiary) {
            if (m.name == name) return &m;
            // == byte-for-byte equality
            // here, & is address-of operator
            // since m is a reference into a vector
            // &m is a pointer to that slot in the
            // vector;
        }
        return nullptr; // c++ typed null pointer
        // NULL macro --> an int 0 in disguise
    }

const Monster* binarySearch(const std::vector<Monster>& bestiary,
                            const std::string&         name) {
    // TODO Floor 1 (Wed): iterative binary search.
    //   PRECONDITION: bestiary is sorted ascending by name.
    int low = 0;
	int high = bestiary.size();
    while (low < high) {
		int mid = low + ((high - low) / 2);
		std::string currentName = bestiary[mid].name;
        if (currentName == name) {
            return &bestiary[mid];
        }
        else if (currentName < name) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
	return nullptr;
}

namespace {
    const Monster* binSearchRec(const std::vector<Monster>& bestiary, const std::string& name, size_t low, size_t high) {
        if (low >= high) { //base case
            return nullptr;
        }
        size_t mid = low + (high - low) / 2;
        const std::string& here = bestiary[mid].name;
        if (here == name) {
            return &bestiary[mid];
        }
        else if (here < name) {
            return binSearchRec(bestiary, name, mid + 1, high);
        }
        else {
            return binSearchRec(bestiary, name, low, mid);
		}
    }
}

const Monster* binarySearchRecursive(const std::vector<Monster>& bestiary,
                                     const std::string&         name) {
    return binSearchRec(bestiary, name, 0, bestiary.size());
    //   - After it works: run `benchmark`. Does the recursive version cost
    //     more per call than the iterative one? A little? A lot? Why might
    //     that be? Write the answer in lab-notes.md.
}

const Monster* findMonster(const std::vector<Monster>& bestiary,
                           const std::string&         name) {
    // TODO Floor 1: pick ONE of the three searches above and delegate.
    //
    // Think before you type:
    //   - At the real bestiary's size (15 monsters), does it matter which
    //     you pick? Run benchmark at N=10 and look at the microseconds.
    //   - At N=100,000, does it matter? By how much?
    //   - This is a JUDGMENT, not a fact. Whatever you pick, write WHY in
    //     your commit message. That reasoning is the graded artifact.
    return binarySearchRecursive(bestiary, name);
    }

}
