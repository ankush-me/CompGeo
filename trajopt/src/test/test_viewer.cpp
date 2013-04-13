#include "osgviewer/simplescene.h"
#include "osgviewer/plotting.h"
#include "osgviewer/util.h"

using namespace Eigen;
using namespace std;

class CustomScene : public Scene{};


int main (int argc, char* argv[]) {
	CustomScene s;
	Eigen::Affine3f tf = Eigen::Affine3f::Identity();
	util::drawAxes(tf, 1.0 ,s.env);


	PlotPolygons::Ptr polys(new PlotPolygons);
	s.env->add(polys);

	vector<Vector3f> verts;
	verts.push_back(Vector3f(1,0,0));
	verts.push_back(Vector3f(0,1,0));
	verts.push_back(Vector3f(0,0,1));
	polys->setDefaultColor(0.6,0.3,0,0.7);
	polys->addPolygon(verts);

	s.run();
}
