/** Data structure based on std::set for holding sweep-line events. */

#ifndef __EVENTQ_H__
#define __EVENTQ_H__

#include <set>
#include <vector>
#include "utils/sorting.h"


/** The class is templatized for the type of points to store.
 * But the line-segment intersection is implemented for 2D case only. */

template <class T, class T_allocator>
class EventQ {

	std::vector<T,T_allocator> * pts;
	IndexedComparator<T,T_allocator> comp;
	std::set<int, IndexedComparator<T,T_allocator> > *Q;



public:

	/** DIM  : the dimension of the points being stored. */
	EventQ (std::vector<T,T_allocator> *_pts, int dim) : pts(_pts), comp(dim, _pts) {
		Q  = new std::set<int, IndexedComparator<T,T_allocator> >(comp);
	}

	bool insert(const int &idx) {
		assert(("EventQ: insert index out of range!", 0<=idx && idx < pts->size()));
		std::pair<std::set<int>::iterator, bool> ret = Q->insert(idx);
		return ret.second;
	}


	// inserts the last point in PTS into the internal binary tree.
	bool insertLast() {
		std::pair<std::set<int>::iterator, bool> ret = Q->insert(pts->size()-1);
		return ret.second;
	}

	void erase(const int &idx) {
		Q->erase(idx);
	}

	int  removeMin () {
		using namespace std;
		if (!Q->empty()) {
			typename std::set<int, IndexedComparator<T, T_allocator> >::iterator it = Q->begin();
			Q->erase(it); // remove the element from the set.
			return *it;
		}
		return -1;
	}

	bool empty() {
		return Q->empty();
	}

};

#endif