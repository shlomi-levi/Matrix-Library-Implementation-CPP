#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(std::vector<std::vector<double>> input) {
	int rows = input.size();
	if(!rows)
		throw std::invalid_argument("Enclosing list is empty. cannot create matrix with 0 rows.");

	int cols = input.at(0).size();

	if(!cols)
		throw std::invalid_argument("First list contains 0 elements. cannot create matrix with 0 columns");

	// Make sure all the rows have the same amount of columns:
	for(int i = 1; i < rows; i++) {
		if(input.at(i).size() != cols)
			throw std::invalid_argument("All of the lists inside the enclosing list must have the same amount of elements, since each row in a matrix has the same number of columns");
	}

	m_matrixData = new double[rows * cols];

	m_numOfRows = rows;
	m_numOfCols = cols;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			m_matrixData[index(i, j)] = input.at(i).at(j);
		}
	}
}

Matrix::Matrix(double** values, int rows, int cols) {
	m_matrixData = new double[rows * cols];

	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			m_matrixData[index(i, j)] = values[i][j];
}

Matrix::Matrix(int rows, int cols) : m_numOfRows(rows), m_numOfCols(cols) {
	m_matrixData = new double[rows * cols];
	std::fill_n(m_matrixData, rows * cols, 0.0);
}

Matrix::Matrix(const Matrix& other) {
	m_matrixData = new double[other.m_numOfRows * other.m_numOfCols];

	m_numOfRows = other.m_numOfRows;
	m_numOfCols = other.m_numOfCols;

	std::copy(&other.m_matrixData[0], &other.m_matrixData[other.m_numOfCols], m_matrixData);
}

Matrix::Matrix(Matrix&& other) {
	m_matrixData = other.m_matrixData;
	m_numOfRows = other.m_numOfRows;
	m_numOfCols = other.m_numOfCols;

	other.m_matrixData = nullptr;
}

Matrix::~Matrix() {
	delete[] m_matrixData;
}

void swap(Matrix& m1, Matrix& m2) {
	std::swap(m1.m_numOfRows, m2.m_numOfRows);
	std::swap(m1.m_numOfCols, m2.m_numOfCols);
	std::swap(m1.m_matrixData, m2.m_matrixData);
}

Matrix& Matrix::operator= (Matrix other) {
	swap(*this, other);
	return *this;
}

Matrix& Matrix::operator+= (const Matrix& other) {
	if(m_numOfRows != other.m_numOfRows || m_numOfCols != other.m_numOfCols)
		throw std::logic_error("In order to add two matrices they must have the same dimensions.");

	for(int i = 0; i < m_numOfRows * m_numOfCols; i++)
		m_matrixData[i] += other.m_matrixData[i];

	return (*this);
}

Matrix Matrix::operator+ (const Matrix& other) const {
	Matrix res { (*this) };
	res += other;
	return res;
}

Matrix Matrix::operator* (const Matrix& other) const {
	if(m_numOfCols != other.m_numOfRows)
		throw std::invalid_argument("When multiplying AxB, the number of columns in a must match the number of rows in B");

	Matrix res {m_numOfRows, other.m_numOfCols};
	
	for(int i = 0 ; i < m_numOfRows ; i++) {
		for(int j = 0 ; j < m_numOfCols ; j++) {
			double currElem = 0;

			for(int k = 0 ; k < m_numOfCols ; k++)
				currElem += ( m_matrixData[index(i, k)] * other.m_matrixData[index(k, j)] );

			res.m_matrixData[index(i, j)] = currElem;
		}
	}
	return res;
};

Matrix& Matrix::operator*= (const Matrix& other) {
	if(m_numOfCols != other.m_numOfRows)
		throw std::invalid_argument("When multiplying AxB, the number of columns in a must match the number of rows in B");

	Matrix res = (*this) * other;

	swap((*this), res);

	return (*this);
}

Matrix& Matrix::operator*= (const double scalar) {
	for(int i = 0; i < m_numOfRows * m_numOfCols; i++)
		m_matrixData[i] *= scalar;

	return (*this);
};

Matrix Matrix::operator* (const double scalar) const {
	Matrix res{ (*this) }; // Initialize res using the copy constructor
	res *= scalar;
	return res;
}

Matrix Matrix::operator[] (const int row) const { };

Matrix Matrix::eliminate() const { };

Matrix& Matrix::transpose() {
	if(m_numOfRows != m_numOfCols)
		throw std::invalid_argument("Only a squared matrix can be transposed");


	for(int i = 1 ; i < m_numOfRows ; i++) {
		for(int j = i + 1 ; j < m_numOfCols ; j++) { 
			double temp = m_matrixData[index(i, j)];

			m_matrixData[index(i, j)] = m_matrixData[index(j, i)];
			m_matrixData[index(j, i)] = temp;
		}
	}
	return (*this);
}

Matrix Matrix::transposed() const {
	if(m_numOfRows != m_numOfCols)
		throw std::invalid_argument("Only a squared matrix can be transposed");

	Matrix res {(*this)};
	res.transpose();

	return res;
};

void Matrix::swapRows(const int row1, const int row2) { };

int Matrix::index(const int row, const int col) const {
	return (row * m_numOfCols) + col;
};
