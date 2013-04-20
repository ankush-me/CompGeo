#include "intersection/eventQ.h"
#include "utils/sorting.h"

#include <Eigen/AlignedVector>
#include <iostream>

using namespace Eigen;
using namespace std;


int main (int argc, char* argv[]) {
	/** get some points. */
	const int N=10;
	MatrixXf randm = MatrixXf::Random(N,2);
	vector2 verts(N);
	for (int i = 0 ; i < N; i+=1) {
		verts[i] = randm.row(i);
	}

	EventQ<Vector2f, allocator2f> eq(&verts, 2);

	for (int i=0; i <N; i ++) {
		cout <<" inserting : "<< verts.size()<<endl;
		eq.insert(i);
	}


	cout << "Removing min [should be in order] ..."<<endl;
	while (!eq.empty()) {
		int idx = eq.removeMin();
		cout << "  " << verts[idx].transpose()<<endl;
	}
}
