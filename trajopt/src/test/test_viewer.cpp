#include "simplescene.h"
#include "plotting.h"
#include "util.h"

class CustomScene : public Scene{

};


int main (int argc, char* argv[]) {
	CustomScene s;
	Eigen::Affine3f tf = Eigen::Affine3f::Identity();
	util::drawAxes(tf, 1.0 ,s.env);
	s.run();
}
