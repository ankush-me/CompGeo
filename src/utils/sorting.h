#pragma once

#include <Eigen/Dense>
#include <vector>


struct Comparator : std::binary_function <Eigen::VectorXf, Eigen::VectorXf, bool> {
	int d; // dimensions of the vector
	Comparator(int _d) : d(_d) {}

	bool operator() (const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) const {
			int i = 0;
			while(i < d && v1[i] == v2[i]) {i++;}
			return (i==d || v1[i] < v2[i]);
		}
};


/** Sort a matrix NxD (N points in D dimensions) lexicographically. In-place. */
void lexicoSort(Eigen::MatrixXf &mat_nd);


/** Sort a vector of points lexicographically. In-place. */

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
void lexicoSort(std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);
