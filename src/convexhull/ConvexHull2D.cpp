/* Computes convex hulls of 2d points. */

#include "ConvexHull2D.h"

#include <iostream>

using namespace std;
using namespace Eigen;


/** Returns the indices of input vertices in clockwise order which form the convex hull.
 * Uses Graham's scan */
vector2 ConvexHull2D::GrahamsConv2d (const vector2 &pts) {

	// sort lexicographically
	vector2 sorted_pts(pts);
	lexicoSort(sorted_pts);

	// construct the lower-hull
	vector2 stack;
	int i = 0;
	while (i < sorted_pts.size()) {
		Vector2f pt = sorted_pts[i];
		i += 1;
		stack.push_back(pt);

		int N = stack.size();
		while(N >= 3 && !ccw(stack[N-3], stack[N-2], stack[N-1])) {
			stack.erase(stack.end()-2);
			N -= 1;
		}
	}

	// construct the upper-hull
	vector2 stack2;
	i = sorted_pts.size()-1;
	while (i >= 0) {
		Vector2f pt = sorted_pts[i];
		i -= 1;
		stack2.push_back(pt);

		int N = stack2.size();
		while(N >= 3 && !ccw(stack2[N-3], stack2[N-2], stack2[N-1])) {
			stack2.erase(stack2.end()-2);
			N -= 1;
		}
	}

	// append the list of upper-hull to the lower-hull
	// (the first and the last vertices of the 2-hulls are the same, hence skip them.)
	for(int c= 1; c < stack2.size()-1;  c++)
		stack.push_back(stack2[c]);

	return stack;
}
