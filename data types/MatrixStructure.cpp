#include "MatrixStructure.h"
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

MatrixStructure operator+(MatrixStructure m1, MatrixStructure m2) {
	if (m2.rows != m1.rows || m1.columns != m2.columns)
		throw runtime_error(
				"Error: Dimensions " + to_string(m1.rows) + "x"
						+ to_string(m1.columns) + " and " + to_string(m2.rows)
						+ "x" + to_string(m2.columns)
						+ " are not compatible with addition");
	MatrixStructure new_array = MatrixStructure(m1.rows, m1.columns);
	for (unsigned int i = 0; i < m1.rows * m1.columns; i++)
		new_array.array[i] = m1.array[i] + m2.array[i];
	return new_array;
}

MatrixStructure operator-(MatrixStructure m1, MatrixStructure m2) {
	if (m2.rows != m1.rows || m1.columns != m2.columns)
		throw runtime_error(
				"Error: Dimensions " + to_string(m1.rows) + "x"
						+ to_string(m1.columns) + " and " + to_string(m2.rows)
						+ "x" + to_string(m2.columns)
						+ " are not compatible with subtraction");
	MatrixStructure new_array = MatrixStructure(m1.rows, m2.columns);
	for (unsigned int i = 0; i < m1.rows * m1.columns; i++)
		new_array.array[i] = m1.array[i] - m2.array[i];
	return new_array;
}

MatrixStructure operator*(MatrixStructure m1, MatrixStructure m2) {
	if (m2.rows != m1.columns)
		throw runtime_error(
				"Error: Dimensions " + to_string(m1.rows) + "x"
						+ to_string(m1.columns) + " and " + to_string(m2.rows)
						+ "x" + to_string(m2.columns)
						+ " are not compatible with multiplication");
	MatrixStructure new_array = MatrixStructure(m1.rows, m2.columns);
	for (unsigned int i = 0; i < m1.rows; i++) {
		for (unsigned int j = 0; j < m2.columns; j++) {
			double sum = 0;
			for (unsigned int k = 0; k < m1.columns; k++) {
				sum += m1(i, k) * m2(k, j);
			}
			new_array(i, j) = sum;
		}
	}
	return new_array;
}
MatrixStructure operator*(double constant,MatrixStructure m) {
	MatrixStructure new_array = MatrixStructure(m.rows, m.columns);
	for (unsigned int i = 0; i < m.rows; i++) {
		for (unsigned int j = 0; j < m.columns; j++) {
			new_array(i, j) = m(i, j) * constant;
		}
	}
	return new_array;
}
MatrixStructure operator*(MatrixStructure m,double constant) {
	return operator*(constant,m);
}
MatrixStructure transpose(MatrixStructure m) {
	MatrixStructure new_m = m;
	new_m.transpose();
	return new_m;
}
void MatrixStructure::transpose() {
	transposed = true;

	unsigned int temp = rows;
	rows = columns;
	columns = temp;
}
double& MatrixStructure::operator()(unsigned int row, unsigned int column) {
	//http://www.cplusplus.com/reference/string/to_string/
	//https://stackoverflow.com/questions/12261915/how-to-throw-stdexceptions-with-variable-messages
	if (row >= rows)
		throw runtime_error(
				"IndexError: " + to_string(row) + " >= " + to_string(rows));
	if (column >= columns)
		throw runtime_error(
				"IndexError: " + to_string(column) + " >= "
						+ to_string(columns));
	if (transposed)
		return array[rows * column + row];
	return array[columns * row + column];
}
