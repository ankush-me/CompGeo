#include "osgviewer/simplescene.h"
#include "osgviewer/plotting.h"
#include "osgviewer/util.h"

#include "utils/geom_predicates.h"
#include "utils/sorting.h"


using namespace Eigen;
using namespace std;

class CustomScene : public Scene{};





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
	polys->setDefaultColor(0.6,0.3,0,0.7);
	polys->addPolygon(verts);

	//draws a sequence of lines connecting a pt to its successor
	util::drawPoly(verts, Vector3f(1,0,0), 1, s.env);


	/** Test orientation function. */
	vector<Vector2f> verts2d;
	verts2d.push_back(Vector2f(0,0));
	verts2d.push_back(Vector2f(1,0));
	verts2d.push_back(Vector2f(0,1));
	cout << " ccw [should be false] : " << (ccw(verts2d[0], verts2d[2], verts2d[1])? "true" : "false") << endl;
	cout << " ccw [should be true]  : " << (ccw(verts2d[0], verts2d[1], verts2d[2])? "true" : "false") << endl;

	/** test lexicographic sorting. */
	//   1.  a row is considered to be a vector.
	MatrixXf mat(4,3);
	mat << 0.21, 0.34, 5,
		   0.21, 0.21, 10,
		   0  ,  1.0 , 0,
		   0,    1.0, 1;
	lexicoSort(mat);
	cout << "sorted mat: "<<endl << mat<<endl;

	//  2. lexico-sort a vector of points.
	lexicoSort(verts);
	for (int i=0; i<verts.size(); i++) {
		cout << verts[i].transpose()<<endl;
	}

	//s.run();
}
