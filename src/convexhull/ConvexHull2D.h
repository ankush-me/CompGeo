/* Computes convex hulls of 2d points. */
#pragma once

#include <Eigen/Dense>
#include <Eigen/AlignedVector>
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
	vector2 GrahamsConv2d (const vector2 &pts);

};
