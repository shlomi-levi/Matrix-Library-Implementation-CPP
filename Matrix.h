#pragma once
#include <vector>

class Matrix {
public:
	Matrix(std::vector<std::vector<double>>);
	Matrix(double**, int, int);
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix(Matrix&&);
	~Matrix();

	friend void swap(Matrix&, Matrix&);

	Matrix& operator= (Matrix);

	Matrix operator+ (const Matrix&) const;
	Matrix& operator+= (const Matrix&);

	Matrix operator* (const Matrix&) const;
	Matrix& operator*= (const Matrix&);

	Matrix operator* (const double) const;
	Matrix& operator*= (const double);

	Matrix operator[] (const int) const;
	
	Matrix eliminate() const;
	Matrix& transpose();
	Matrix transposed() const;

	void swapRows(const int, const int);

	int index(const int, const int) const;

private:
	double* m_matrixData;
	int m_numOfRows;
	int m_numOfCols;
};