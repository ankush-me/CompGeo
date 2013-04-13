#include "sorting.h"
#include <algorithm>

#include <algorithm>

using namespace Eigen;
using namespace std;


/** Comparator used in sorting vectors. */
bool Comparator::operator() (const VectorXf &v1, const VectorXf &v2) const {
	int i = 0;
	while(i < d && v1[i] == v2[i]) {i++;}
	return (i==d || v1[i] < v2[i]);
}


/** Sort a matrix NxD (N points in D dimensions) lexicographically. In-place. */
void lexicoSort(Eigen::MatrixXf &mat_nd) {
	int n = mat_nd.rows();
	int d = mat_nd.cols();

	vector<VectorXf> dat(n);
	for (int i=0; i<n; i++)
		dat[i] = mat_nd.row(i);

	sort(dat.begin(), dat.end(), Comparator(d));

	//copy back
	for (int i=0; i<n; i++)
		mat_nd.row(i) = dat[i];
}


/** Sort a vector of points lexicographically. In-place.*/
template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
void lexicoSort(vector<Matrix<T, R, C, _Options, _MaxRows, _MaxCols> >& mat_nd) {
	int n = mat_nd.size();
	if (n != 0) {
		int d = mat_nd[0].rows();
		sort(mat_nd.begin(), mat_nd.end(), Comparator(d));
	}
}

/** Force the compiler to generate the following instantiations of lexicoSort. */
template void lexicoSort  (std::vector<Eigen::Vector2f> & mat);
template void lexicoSort  (std::vector<Eigen::Vector3f> & mat);
template void lexicoSort  (std::vector<Eigen::VectorXf> & mat);
