/* Computes convex hulls of 2d points. */
#pragma once

#include <Eigen/Dense>
#include <Eigen/AlignedVector>
#include <vector>
#include "utils/sorting.h"
#include "utils/geom_predicates.h"
#include "osgviewer/plotting.h"

using namespace std;
using namespace Eigen;


class ConvexHull2D {

	/** Finds the clockwise most point in the vector of points pts wrt pt.
	 *  pts are assumed to be vertices of convex polygon in ccw direction.
	 *  Plus, it is assumed that START is such that a linear search suffices when starting from PTS[start].
	 *
	 *  This is used in Chan's shattering algorithm. */
	int cw_most(const vector2 &pts, int start, const Vector2f &pt);


public:

	enum Algo {
		GRAHAMS,
		JARVIS,
		CHANS
	};

	/** Returns the vertices in clockwise order which form the convex hull.
	 * Uses Graham's scan : O[n log(n)]. */
	vector2 GrahamsConv2d (const vector2 &pts);

	/** Returns the vertices in clockwise order which form the convex hull.
	 * Uses Jarvis' march [gift-wrapping algorithm] : O[nh]. */
	vector2 JarvisConv2d (const vector2 &pts);

	/** Returns the vertices in clockwise order which form the convex hull.
		 * Uses Chan's shattering algorithm : O[n log(h)]. */
	vector2 ShatteringConv2d (const vector2 &pts, int h);

};
