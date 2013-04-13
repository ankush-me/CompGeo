#include "osgviewer/simplescene.h"
#include "osgviewer/plotting.h"
#include "osgviewer/util.h"

#include "utils/geom_predicates.h"
#include "utils/sorting.h"
#include "convexhull/ConvexHull2D.h"

using namespace Eigen;
using namespace std;

class CustomScene : public Scene{};



vector<Vector3f> to3d(const vector<Vector2f> &pts) {
	vector<Vector3f> pts3d(pts.size());
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

	vector<Vector3f> verts;
	verts.push_back(Vector3f(1,0,0));
	verts.push_back(Vector3f(0,1,0));
	verts.push_back(Vector3f(0,0,1));
	//polys->setDefaultColor(0.6,0.3,0,0.7);
	//polys->addPolygon(verts);

	//draws a sequence of lines connecting a pt to its successor
	//util::drawPoly(verts, Vector3f(1,0,0), 1, s.env);


	/** Test orientation function. */
	vector<Vector2f> verts2d;
	verts2d.push_back(Vector2f(0,0));
	verts2d.push_back(Vector2f(2,0));
	verts2d.push_back(Vector2f(0,1));
	verts2d.push_back(Vector2f(1,0.5));
	verts2d.push_back(Vector2f(1,0.7));
	verts2d.push_back(Vector2f(1.1,1.4));

	vector<Vector3f> pts3d = to3d(verts2d);
	util::drawPoly(pts3d, Vector3f(1,0,0), 1, s.env);


	ConvexHull2D conv;
	vector<Vector2f> conv_pts = conv.GrahamsConv2d(verts2d);
	vector<Vector3f> pts3d2 = to3d(conv_pts);

	util::drawSpheres(pts3d2, Vector3f(0,1,0), 1, 0.1, s.env);

	s.run();
}
