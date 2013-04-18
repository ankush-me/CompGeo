/* Computes convex hulls of 2d points. */

#include "ConvexHull2D.h"

#include <iostream>
#include "utils/misc.h"

using namespace std;
using namespace Eigen;


vector2 ConvexHull2D::conv(const vector2 &pts, Algo alg, int h) {
	switch (alg) {
	case GRAHAMS:
		return GrahamsConv2d(pts);
		break;
	case JARVIS:
		return JarvisConv2d(pts);
		break;
	case CHANS:
		return ShatteringConv2d(pts, h);
		break;
	default:
		return GrahamsConv2d(pts);
	}
}


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


vector2 ConvexHull2D::ShatteringConv2d (const vector2 &pts, const int h) {
	cout << "   >> Chan's : h = "<<h<<endl;

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
			cw_inds[i]  = cw_most2(conv_hulls[i], cw_inds[i], p);
			cw_mosts[i] = conv_hulls[i][cw_inds[i]];
		}
		Vector2f q = cw_mosts[cw_most(cw_mosts, 0, p)];
		conv_pts.push_back(p);

		p = q;
		step += 1;
	} while(step < h && !areEqual(p, all_min_pt));


	if (!areEqual(p, all_min_pt)) {
		cout << "     -- recursing with : h = "<<h*h<<endl;
		return ShatteringConv2d (pts, h*h);
	} else {
		cout << "     -- returning with : h = "<<h<<endl;
		return conv_pts;
	}
}



/** Find the cw most point in pts wrt pt. Starting at index s, going up to N.*/
int ConvexHull2D::cw_most2(const vector2 &pts, const int s, const Vector2f &pt) {

	const int N = pts.size();
	if (N==1) return 0;

	int i = s;
	while(pts[i]==pt && in_range(i,s,0,N)) {i = mod(i+1,N);}

	while(in_range(i,s,0,N)) {
		if (ccw(pt, pts[mod(i+1,N)], pts[i])) {
			i = mod(i+1,N);
		} else {
			break;
		}
	}
	return i;
}


/** CW-most tests which just goes over all points and returns the cw most wrt pt. */
int ConvexHull2D::cw_most(const vector2 &pts, int start, const Vector2f &pt) {

	const int N = pts.size();
	if (N==1) return 0;

	int p = lexicoMin(pts);
	while (pt==pts[p]) {p = (p+1)%N;}

	for (int r=0; r < N; r+=1) {
		if (r==p || pts[r]==pt) continue;
		if (ccw(pt, pts[r], pts[p]))
			p = r;
	}
	return p;
}
