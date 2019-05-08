#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() {
	rows = 0;
	columns = 0;
	return;
}
Matrix Matrix::operator=(MatrixStructure other) {
	transposed = other.transposed;
	array = other.array;
	columns = other.columns;
	rows = other.rows;
	return *this;
}
unsigned int Matrix::get_rows() const {
	return rows;
}
unsigned int Matrix::get_columns() const {
	return columns;
}

Matrix::Matrix(unsigned int rows, unsigned int columns) :
		MatrixStructure(rows, columns) {
	return;
}

IdentityMatrix::IdentityMatrix(unsigned int size) :
		Matrix(size, size) {
	for (unsigned int i = 0; i < size; i++)
		(*this)(i, i) = 1;
}

Vector::Vector() {
	rows = 0;
	columns = 0;
}
Vector Vector::operator=(MatrixStructure other) {
	transposed = other.transposed;
	array = other.array;
	columns = other.columns;
	rows = other.rows;
	return *this;
}

double& Vector::operator()(unsigned int index) {
	if (index >= get_size())
		throw runtime_error(
				"IndexError: " + to_string(index) + " >= "
						+ to_string(get_size()));
	return array[index];
}

double& Vector::operator()(unsigned int row, unsigned int column) {
	return MatrixStructure::operator()(row, column);
}
Vector::Vector(unsigned int size) :
		MatrixStructure(size, 1) {
	for (unsigned int i = 0; i < size; i++)
		(*this)(i) = 0;
}
unsigned int Vector::get_size() const {
	if (columns != 1)
		return columns;
	return rows;
}
