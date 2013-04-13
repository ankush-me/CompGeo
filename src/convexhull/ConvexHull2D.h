/* Computes convex hulls of 2d points. */
#pragma once

#include <Eigen/Dense>
#include <vector>
#include "utils/sorting.h"
#include "utils/geom_predicates.h"


using namespace std;
using namespace Eigen;



class ConvexHull2D {
public:

	enum Algo {
		GRAHAMS,
		JARVINS,
		CHANS
	};

	/** Returns the indices of input vertices in clockwise order which form the convex hull.
	 * Uses Graham's scan */
	vector<Vector2f> GrahamsConv2d (const vector<Vector2f> &pts);

};
