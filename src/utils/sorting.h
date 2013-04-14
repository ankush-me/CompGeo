#pragma once

#include <Eigen/Dense>
#include <Eigen/AlignedVector>
#include <vector>


struct Comparator : std::binary_function <Eigen::VectorXf, Eigen::VectorXf, bool> {
	int d; // dimensions of the vector
	Comparator(int _d) : d(_d) {}

	bool operator() (const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) const;
};


/** Sort a matrix NxD (N points in D dimensions) lexicographically. In-place. */
void lexicoSort(Eigen::MatrixXf &mat_nd);


/** Sort a vector of points lexicographically. In-place. */
template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
void lexicoSort(std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);

/** Sort a vector of points lexicographically. In-place. Redefined for aligned-vectors.*/
template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
void lexicoSort(std::vector<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols>,
		          Eigen::aligned_allocator<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols> > >& mat_nd);



/** Returns the lexicographically minimum point in a list of points.*/
Eigen::VectorXf lexicoMin(const Eigen::MatrixXf &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols>
lexicoMin(const std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols>
lexicoMin(const std::vector<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols>,
		          Eigen::aligned_allocator<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols> > >& mat_nd);



/** Returns the lexicographically maximum point in a list of points.*/
Eigen::VectorXf lexicoMax(const Eigen::MatrixXf &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols>
lexicoMax(const std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols>
lexicoMax(const std::vector<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols>,
		          Eigen::aligned_allocator<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols> > >& mat_nd);


