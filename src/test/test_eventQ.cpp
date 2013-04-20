#include "intersection/eventQ.h"
#include "utils/sorting.h"

#include <Eigen/AlignedVector>
#include <iostream>

using namespace Eigen;
using namespace std;


int main (int argc, char* argv[]) {
	/** get some points. */
	const int N=10;
	MatrixXf randm = MatrixXf::Random(N,10);
	vectorX verts(N);
	for (int i = 0 ; i < N; i+=1) {
		verts[i] = randm.row(i);
	}

	EventQ<VectorXf, allocatorXf> eq(&verts, 10);
	for (int i=0; i <N; i ++) {
		eq.insert(i);
	}

	bool insert = eq.insertLast();
	cout << "Illegal insert. Did insert? : "<<(insert?"True": "False")<<endl;

	cout << " Search result : "<< eq.find(verts.size()-1)<<endl;

	cout << "Removing min [should be in order] ..."<<endl;
	while (!eq.empty()) {
		int idx = eq.removeMin();
		cout << "  " << verts[idx].transpose()<<endl;
	}
}
