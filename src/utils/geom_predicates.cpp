#include "geom_predicates.h"

// Shewchuk's robust predicates
extern "C" {
	#include "predicates.c"
}


double orient2d (Eigen::Vector2d pa, Eigen::Vector2d pb, Eigen::Vector2d pc) {
	return (double) orient2d(pa.data(), pb.data(), pc.data());
}


bool ccw(Eigen::Vector2d pa, Eigen::Vector2d pb, Eigen::Vector2d pc) {
	return orient2d(pa, pb, pc) > 0.0;
}


bool ccw(Eigen::Vector2f pa, Eigen::Vector2f pb, Eigen::Vector2f pc) {
	Eigen::Vector2d v1((double) pa[0], (double) pa[1]);
	Eigen::Vector2d v2((double) pb[0], (double) pb[1]);
	Eigen::Vector2d v3((double) pc[0], (double) pc[1]);
	return ccw(v1, v2, v3);
}


bool cw(Eigen::Vector2d pa, Eigen::Vector2d pb, Eigen::Vector2d pc) {
	return orient2d(pa, pb, pc) < 0.0;
}

bool cw(Eigen::Vector2f pa, Eigen::Vector2f pb, Eigen::Vector2f pc) {
	Eigen::Vector2d v1((double) pa[0], (double) pa[1]);
	Eigen::Vector2d v2((double) pb[0], (double) pb[1]);
	Eigen::Vector2d v3((double) pc[0], (double) pc[1]);
	return cw(v1, v2, v3);
}
