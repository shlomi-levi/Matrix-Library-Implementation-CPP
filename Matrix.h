#pragma once
#include <vector>

enum OP {
	SUBTRACT,
	ADD
};

class Matrix {
public:
	Matrix(std::vector<std::vector<double>>);
	Matrix(double**, int, int);
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	~Matrix();

	friend void swap(Matrix&, Matrix&);

	Matrix& operator= (Matrix);

	Matrix operator+ (const Matrix&) const;
	Matrix& operator+= (const Matrix&);

	Matrix operator* (const Matrix&) const;
	Matrix& operator*= (const Matrix&);

	Matrix operator* (const double) const;
	Matrix& operator*= (const double);

	Matrix eliminate(bool) const;
	Matrix& transpose();
	Matrix transposed() const;

	void swapRows(const int, const int);
	void multiplyRow(int rowNum, double val);
	void addOrSubtractMultipleOfDiffRow(const int dstRow, const int srcRow, const double multiple, const enum OP operation);

	int index(const int, const int) const;

private:
	double* m_matrixData;
	int m_numOfRows;
	int m_numOfCols;
};