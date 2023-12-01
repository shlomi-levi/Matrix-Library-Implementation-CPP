#include <iostream>
#include <vector>
#include "Matrix.h"

using std::cout;

int main() {
	int arr[2][6] = {{1, 2, 3, 4, 9, 8}, {3, 4, 8, 7, 6}};
	std::vector<std::vector<double>> matrix;

	for(int i = 0 ; i < 2 ; i++) {
		std::vector<double> list;

		for(int j = 0 ; j < 6 ; j++)
			list.push_back(arr[i][j]);
		
		matrix.push_back(list);
	}

	Matrix m {matrix};
	cout << m << "\n\n";
	cout << m.transposed() << "\n\n";

	Matrix d = m.eliminate();
	cout << d;

}