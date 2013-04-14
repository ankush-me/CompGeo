#include "osgviewer/simplescene.h"
#include "osgviewer/plotting.h"
#include "osgviewer/util.h"

#include "utils/geom_predicates.h"
#include "utils/sorting.h"
#include "convexhull/ConvexHull2D.h"

#include <Eigen/AlignedVector>

using namespace Eigen;
using namespace std;

class CustomScene : public Scene{};



vector<Vector3f> to3d(const vector2 &pts) {
	vector3 pts3d(pts.size());
	for(int i =0 ; i < pts.size(); i++ ) {
		Vector2f pt = pts[i];
		pts3d[i] = Vector3f(pt.x(), pt.y(), 0);
	}

	return pts3d;
}



int main (int argc, char* argv[]) {
	CustomScene s;
	Eigen::Affine3f tf = Eigen::Affine3f::Identity();
	util::drawAxes(tf, 0.5, s.env);


	PlotPolygons::Ptr polys(new PlotPolygons);
	s.env->add(polys);

	vector3 verts;
	verts.push_back(Vector3f(1,0,0));
	verts.push_back(Vector3f(0,1,0));
	verts.push_back(Vector3f(0,0,1));
	//polys->setDefaultColor(0.6,0.3,0,0.7);
	//polys->addPolygon(verts);

	//draws a sequence of lines connecting a pt to its successor
	//util::drawPoly(verts, Vector3f(1,0,0), 1, s.env);


	/** Test convex-hull function. */

	/** TEST 1. */
//	vector<Vector2f> verts2d;
//	verts2d.push_back(Vector2f(0,0));
//	verts2d.push_back(Vector2f(2,0));
//	verts2d.push_back(Vector2f(0,1));
//	verts2d.push_back(Vector2f(1,0.5));
//	verts2d.push_back(Vector2f(1,0.7));
//	verts2d.push_back(Vector2f(1.1,1.4));
//	vector<Vector3f> pts3d = to3d(verts2d);
//	ConvexHull2D conv;
//	vector<Vector2f> conv_pts = conv.GrahamsConv2d(verts2d);
//	vector<Vector3f> pts3d2 = to3d(conv_pts);
//	util::drawPoly(pts3d, Vector3f(1,0,0), 1, s.env);
//	util::drawSpheres(pts3d2, Vector3f(0,1,0), 1, 0.1, s.env);


	MatrixXf randm = MatrixXf::Random(100,2);
	vector2 verts2d_2(100);
	for (int i = 0 ; i < 100; i+=1) {
		verts2d_2[i] = randm.row(i);
	}
	vector3 pts3d = to3d(verts2d_2);
	ConvexHull2D conv;
	vector2 conv_pts = conv.GrahamsConv2d(verts2d_2);
	vector3 pts3d2 = to3d(conv_pts);
	util::drawPoly(pts3d2, Vector3f(1,0,0), 1, s.env);
	util::drawSpheres(pts3d, Vector3f(0,1,0), 1, 0.01, s.env);

	s.run();
}
