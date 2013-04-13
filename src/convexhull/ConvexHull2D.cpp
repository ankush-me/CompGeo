/* Computes convex hulls of 2d points. */

#include "ConvexHull2D.h"

#include <iostream>

using namespace std;
using namespace Eigen;


/** Returns the indices of input vertices in clockwise order which form the convex hull.
 * Uses Graham's scan */
vector<Vector2f> ConvexHull2D::GrahamsConv2d (const vector<Vector2f> &pts) {

	vector<Vector2f> sorted_pts(pts);
	lexicoSort(sorted_pts);

	vector<Vector2f> stack;

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

	vector<Vector2f> stack2;
	i = 0;
	while (i < sorted_pts.size()) {
		Vector2f pt = sorted_pts[i];
		i += 1;
		stack2.push_back(pt);

		int N = stack2.size();
		while(N >= 3 && !cw(stack2[N-3], stack2[N-2], stack2[N-1])) {
			stack2.erase(stack2.end()-2);
			N -= 1;
		}
	}

	cout << "stack2: "<< stack2.size() << endl;
	for(int c= stack2.size(); c >= 0; c--)
		stack.push_back(stack2[c]);

	for(int c=0; c < stack.size(); c++) {
		cout << stack[c].transpose() <<endl;
	}



	return stack;
}

