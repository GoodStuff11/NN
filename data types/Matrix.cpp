#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(unsigned int rows, unsigned int columns) {
	this->columns = columns;
	this->rows = rows;

	matrix = new double[rows * columns];
	for (unsigned int i = 0; i < rows * columns; i++)
		matrix[i] = 0;
}

Matrix::~Matrix() {
	delete matrix;
}

double& Matrix::operator()(unsigned int row, unsigned int column) {
	return matrix[columns * row + column];
}

void Matrix::print() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			cout << (*this)(i, j) << ' ';
		}
		cout << endl;
	}
}

Matrix* Matrix::operator+(Matrix other) {
	Matrix *new_matrix = new Matrix(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_matrix->matrix[i] = this->matrix[i] + other.matrix[i];
	return new_matrix;
}

Matrix* Matrix::operator-(Matrix other) {
	Matrix *new_matrix = new Matrix(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_matrix->matrix[i] = this->matrix[i] - other.matrix[i];
	return new_matrix;
}

Matrix* Matrix::operator*(Matrix other) {
	Matrix *new_matrix = new Matrix(rows, other.columns);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < other.columns; j++) {
			double sum = 0;
			for (unsigned int k = 0; k < columns; k++) {
				sum += (*this)(i,k)*other(k,j);
			}
			(*new_matrix)(i,j) = sum;
		}
	}
	return new_matrix;
}
