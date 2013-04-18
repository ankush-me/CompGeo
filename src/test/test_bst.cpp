#include "utils/BST.h"


/** Small test for BST code. */
int main (int argc, char**argv) {

	BinarySearchTree<int> T;

	const int N=10;
	for(int i=0; i<N; i++)
		T.Insert(i);

	T.Balance();
	T.PrintTree();
}
