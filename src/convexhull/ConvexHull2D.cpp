/* Computes convex hulls of 2d points. */

#include "ConvexHull2D.h"

#include <iostream>

using namespace std;
using namespace Eigen;





/** Returns the indices of input vertices in clockwise order which form the convex hull.
 * Uses Graham's scan */
vector2 ConvexHull2D::GrahamsConv2d (const vector2 &pts) {

	if (pts.size() <= 2) // easy-case.
		return pts;

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


/** Returns the vertices in clockwise order which form the convex hull.
 * Uses Jarvis' march */
vector2 ConvexHull2D::JarvisConv2d (const vector2 &pts) {
	vector2 conv_pts;
	const int N = pts.size();

	int lexico_min = lexicoMin(pts);
	int p = lexico_min;

	do {
		int q = 0;
		while (q < N && q==p) {q += 1;};  // choose q such that q!=p

		for (int r=0; r < N; r+=1) {
			if (r==p || r==q) continue;
			if (ccw(pts[p], pts[r], pts[q]))
				q =r;
		}
		conv_pts.push_back(pts[p]);
		p = q;
	} while (p != lexico_min);
	return conv_pts;
}



vector3 to3d1(const vector2 &pts) {
	vector3 pts3d(pts.size());
	for(int i =0 ; i < pts.size(); i++ ) {
		Vector2f pt = pts[i];
		pts3d[i] = Vector3f(pt.x(), pt.y(), 0);
	}

	return pts3d;
}


vector2 ConvexHull2D::ShatteringConv2d (const vector2 &pts, const int h) {
	const int N = pts.size();
	const int S = (int) ceil(N/((float) h));

	vector<vector2> sub_sets(S);

	// sub-divide into sets with h points each.
	for(int i=0; i < S; i+=1) {
		const int num_pts = min(h, N-i*h);
		vector2 s_i;
		for(int k=0; k< num_pts; k+=1)
			s_i.push_back(pts[i*h+k]);

		sub_sets[i] = s_i;
	}

	// find convex hulls of the sub-sets using Graham's scan.
	vector<vector2> conv_hulls(S);
	for(int i=0; i< S; i+=1) {
		vector2 conv_i = GrahamsConv2d(sub_sets[i]);
		conv_hulls[i] = conv_i;
	}

	// find the lexico-graphically minimum points of the subset == lexico-min of convex hulls of the sub-sets
	vector<int> lexico_min_idx(S);
	vector2 lexico_min_pts(S);
	for (int i=0; i<S; i++) {
		lexico_min_idx[i] = lexicoMin(conv_hulls[i]);
		lexico_min_pts[i] = conv_hulls[i][lexico_min_idx[i]];
	}
	int all_min = lexicoMin(lexico_min_pts);
	Vector2f all_min_pt = lexico_min_pts[all_min];


	EqComparator areEqual(2);

	// store the final convex-hulls points
	vector2 conv_pts;

	// store indices of cw most points from p in the sub-sets
	vector<int> cw_inds(S, 0);
	vector2 cw_mosts(S);

	int step =0;
	// Do Jarvis' march from all_min
	Vector2f p = all_min_pt;
	do {
		for (int i=0; i<S; i+=1) {
			cw_inds[i]  = cw_most(conv_hulls[i], cw_inds[i], p);
			cw_mosts[i] = conv_hulls[i][cw_inds[i]];
		}
		Vector2f q = cw_mosts[cw_most(cw_mosts, 0, p)];
		conv_pts.push_back(p);

		p = q;
		step += 1;
	} while(step < h && !areEqual(p, all_min_pt));

	if (!areEqual(p, all_min_pt)) {
		return ShatteringConv2d (pts, h*h);
	} else {
		return conv_pts;
	}
}



int ConvexHull2D::cw_most(const vector2 &pts, int start, const Vector2f &pt) {

	if (pts.size()==1)
		return 0;

	EqComparator eq(2);

	int p = start;
	while(eq(pt, pts[p])) {
		p = (p==pts.size()-1)? 0: p+1;
	}

	do {
		int q = (p==pts.size()-1)? 0: p+1;

		if (ccw(pt, pts[q], pts[p])) {
			p = q;
		} else {
			break;}
	} while(p!=start);
	return p;
}
