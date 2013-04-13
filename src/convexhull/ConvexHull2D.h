/* Computes convex hulls of 2d points. */

#include <Eigen/Dense>
#include <vector>

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
	vector<int> GrahamsConv2d (const vector<Vector2f> pts) {
		vector<int> lexicoOrder(pts);
	}


};
