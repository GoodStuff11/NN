#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() {
	return;
}
Matrix::Matrix(unsigned int rows, unsigned int columns) {
	this->columns = columns;
	this->rows = rows;

	matrix.resize(rows * columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		matrix[i] = 0;
}

double& Matrix::operator()(unsigned int row, unsigned int column) {
	return matrix[columns * row + column];
}
double& Matrix::operator()(unsigned int row) {
	return matrix[row * columns];
}
Matrix Matrix::transpose() {
	Matrix new_matrix = Matrix(columns, rows);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			new_matrix(j, i) = (*this)(i, j);
		}
	}
	return new_matrix;
}
void Matrix::print() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			cout << (*this)(i, j) << ' ';
		}
		cout << endl;
	}
}

Matrix Matrix::operator+(Matrix other) {
	Matrix new_matrix = Matrix(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_matrix.matrix[i] = this->matrix[i] + other.matrix[i];
	return new_matrix;
}
Matrix Matrix::operator=(Matrix other) {
	matrix = other.matrix;
	columns = other.columns;
	rows = other.rows;
	return *this;
}

Matrix Matrix::operator-(Matrix other) {
	Matrix new_matrix = Matrix(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_matrix.matrix[i] = this->matrix[i] - other.matrix[i];
	return new_matrix;
}

Matrix Matrix::operator*(Matrix other) {
	Matrix new_matrix = Matrix(rows, other.columns);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < other.columns; j++) {
			double sum = 0;
			for (unsigned int k = 0; k < columns; k++) {
				sum += (*this)(i, k) * other(k, j);
			}
			new_matrix(i, j) = sum;
		}
	}
	return new_matrix;
}

IdentityMatrix::IdentityMatrix(unsigned int size) :
		Matrix(size, size) {
	for (unsigned int i = 0; i < size; i++)
		(*this)(i, i) = 1;
}
Vector::Vector(unsigned int size) :
		Matrix(size, 1) {
	for (unsigned int i = 0; i < size; i++)
		(*this)(i) = 1;
}
