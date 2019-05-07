#include "Matrix.h"
#include <iostream>
#include <stdexcept>

using namespace std;

MatrixStructure::MatrixStructure() {
	transposed = false;
	rows = 0;
	columns = 0;
}
MatrixStructure::MatrixStructure(unsigned int rows, unsigned int columns) {
	transposed = false;
	this->columns = columns;
	this->rows = rows;

	array.resize(rows * columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		array[i] = 0;
}

void MatrixStructure::print() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			cout << (*this)(i, j) << ' ';
		}
		cout << endl;
	}
}

MatrixStructure MatrixStructure::operator+(MatrixStructure other) {
	MatrixStructure new_array = MatrixStructure(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_array.array[i] = this->array[i] + other.array[i];
	return new_array;
}

MatrixStructure MatrixStructure::operator-(MatrixStructure other) {
	MatrixStructure new_array = MatrixStructure(rows, columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		new_array.array[i] = this->array[i] - other.array[i];
	return new_array;
}

MatrixStructure MatrixStructure::operator*(MatrixStructure other) {
	MatrixStructure new_array = MatrixStructure(rows, other.columns);
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < other.columns; j++) {
			double sum = 0;
			for (unsigned int k = 0; k < columns; k++) {
				sum += (*this)(i, k) * other(k, j);
			}
			new_array(i, j) = sum;
		}
	}
	return new_array;
}
MatrixStructure MatrixStructure::transpose() {
	transposed = true;

	unsigned int temp = rows;
	rows = columns;
	columns = temp;

	return *this;
}

Matrix::Matrix() {
	rows = 0;
	columns = 0;
	return;
}
Matrix Matrix::operator=(MatrixStructure other) {
	transposed = MatrixStructure::transposed;
	array = MatrixStructure::array;
	columns = MatrixStructure::columns;
	rows = MatrixStructure::rows;
	return *this;
}
unsigned int Matrix::get_rows() {
	//if (transposed)
	//	return columns;
	return rows;
}
unsigned int Matrix::get_columns() {
	//if (transposed)
	//	return rows;
	return columns;
}
double& MatrixStructure::operator()(unsigned int row, unsigned int column) {
	//http://www.cplusplus.com/reference/string/to_string/
	//https://stackoverflow.com/questions/12261915/how-to-throw-stdexceptions-with-variable-messages
	if (transposed) {
		unsigned int temp = row;
		row = column;
		column = temp;
	}
	if (row >= rows)
		throw runtime_error(
				"IndexError: " + to_string(row) + " >= " + to_string(rows));
	if (column >= columns)
		throw runtime_error(
				"IndexError: " + to_string(column) + " >= "
						+ to_string(columns));
	return array[columns * row + column];
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
	//https://en.cppreference.com/w/cpp/language/access
	//kinda inspired by this, but i mostly just guessed and it worked
	transposed = MatrixStructure::transposed;
	array = MatrixStructure::array;
	columns = MatrixStructure::columns;
	rows = MatrixStructure::rows;
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
unsigned int Vector::get_size() {
	if (columns != 1)
		return columns;
	return rows;
}
