#pragma once
#include <vector>
#include <iostream>

enum OP {
	SUBTRACT,
	ADD
};

class Matrix {
	friend void swap(Matrix&, Matrix&);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

public:
	Matrix(std::vector<std::vector<double>>);
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	~Matrix();

	Matrix& operator= (Matrix);

	Matrix operator+ (const Matrix&) const;
	Matrix& operator+= (const Matrix&);

	Matrix operator* (const Matrix&) const;
	Matrix& operator*= (const Matrix&);

	Matrix operator* (const double) const;
	Matrix& operator*= (const double);

	Matrix eliminate(bool isHomogenous=true) const;
	Matrix& transpose();
	Matrix transposed() const;

	int index(const int, const int) const;

private:
	double* m_matrixData;
	int m_numOfRows;
	int m_numOfCols;

	void swapRows(const int, const int);
	void multiplyRow(int rowNum, double val);
	void addOrSubtractMultipleOfDiffRow(const int dstRow, const int srcRow, const double multiple, const enum OP operation);
};