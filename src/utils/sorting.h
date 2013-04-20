#pragma once

#include <Eigen/Dense>
#include <Eigen/AlignedVector>
#include <vector>

#include <iostream>

struct Comparator : std::binary_function <Eigen::VectorXf, Eigen::VectorXf, bool> {
	int d; // dimensions of the vector
	Comparator(int _d) : d(_d) {}

	bool operator() (const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) const;
};


struct EqComparator : std::binary_function <Eigen::VectorXf, Eigen::VectorXf, bool> {
	int d; // dimensions of the vector
	EqComparator(int _d) : d(_d) {}

	bool operator() (const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) const;
};


/** Templatized comparator for lexicographic less-than test.
 *  The comparisons are made of the indices based on the points stores in PTS.*/
template <typename T, typename T_allocator>
struct IndexedComparator : std::binary_function <int, int, bool> {
private:
	int d; // dimensions of the vector
	std::vector<T, T_allocator> * pts;
	const int N;

public:
	IndexedComparator(int _d, std::vector<T, T_allocator> *_pts) : d(_d), pts(_pts), N(_pts->size()) {
		std::cout << " size: "<<N<<std::endl;
	}

	void setPts(std::vector<T, T_allocator> * _pts) {
		pts = _pts;
		N   = pts->size();
	}

	bool operator() (const int &i1, const int &i2) const {
		std::cout <<" compare: " << i1 << " | " << i2 << " | size: " << pts->size() << std::endl;
		assert(("IndexedComparator: Indices out of range!", 0<=i1 && i1<N &&  0<=i2 && i2<N ));

		int i = 0;
		while(i < d && pts->at(i1)[i] == pts->at(i2)[i]) {i++;}
		return (i==d || pts->at(i1)[i] < pts->at(i2)[i]);
	}

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



/** Returns the index of the lexicographically minimum point in a list of points.*/
int lexicoMin(const Eigen::MatrixXf &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
int lexicoMin(const std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
int lexicoMin(const std::vector<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols>,
		Eigen::aligned_allocator<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols> > >& mat_nd);



/** Returns the index of the lexicographically maximum point in a list of points.*/
int lexicoMax(const Eigen::MatrixXf &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
int lexicoMax(const std::vector<Eigen::Matrix<T, R,C,  _Options, _MaxRows, _MaxCols> > &mat_nd);

template <typename T, int R, int C, int _Options, int _MaxRows, int _MaxCols>
int lexicoMax(const std::vector<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols>,
		Eigen::aligned_allocator<Eigen::Matrix<T, R, C, _Options, _MaxRows, _MaxCols> > >& mat_nd);


