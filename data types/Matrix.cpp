#include "Matrix.h"

#include <iostream>
#include <stdexcept>

Matrix::Matrix() {
	rows = 0;
	columns = 0;
}
Matrix Matrix::operator=(Matrix other) {
	transposed = other.transposed;
	array = other.array;
	columns = other.get_columns();
	rows = other.get_rows();
	return *this;
}
unsigned int Matrix::get_rows() const {
	return rows;
}
unsigned int Matrix::get_columns() const {
	return columns;
}

Matrix::Matrix(unsigned int rows, unsigned int columns) {
	transposed = false;
	this->columns = columns;
	this->rows = rows;

	array.resize(rows * columns);
	for (unsigned int i = 0; i < rows * columns; i++)
		array[i] = 0;
}
void Matrix::print() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			std::cout << (*this)(i, j) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
Matrix operator+(Matrix m1, Matrix m2) {
	for (unsigned int i = 0; i < m1.get_rows(); i++)
		for (unsigned int j = 0; j < m1.get_columns(); j++)
			m1(i, j) += m2(i, j);
	return m1;
}
Matrix operator-(Matrix m1, Matrix m2) {
	for (unsigned int i = 0; i < m1.get_rows(); i++)
		for (unsigned int j = 0; j < m1.get_columns(); j++)
			m1(i, j) -= m2(i, j);
	return m1;
}
Matrix operator*(Matrix m1, Matrix m2) {
	if (m2.get_rows() != m1.get_columns())
		throw std::runtime_error(
				"Error: Dimensions " + std::to_string(m1.get_rows()) + "x"
						+ std::to_string(m1.get_columns()) + " and "
						+ std::to_string(m2.get_rows()) + "x"
						+ std::to_string(m2.get_columns())
						+ " are not compatible with multiplication");
	Matrix new_array = Matrix(m1.get_rows(), m2.get_columns());
	for (unsigned int i = 0; i < m1.get_rows(); i++) {
		for (unsigned int j = 0; j < m2.get_columns(); j++) {
			double sum = 0;
			for (unsigned int k = 0; k < m1.get_columns(); k++) {
				sum += m1(i, k) * m2(k, j);
			}
			new_array(i, j) = sum;
		}
	}
	return new_array;
}
Vector operator*(Matrix m, Vector v) {
	if (v.get_size() != m.get_columns())
		throw std::runtime_error(
				"Error: Dimensions " + std::to_string(m.get_rows()) + "x"
						+ std::to_string(m.get_columns()) + " and "
						+ std::to_string(v.get_size()) + "x"
						+ std::to_string(m.get_columns())
						+ " are not compatible with multiplication");
	Vector new_vector = Vector(m.get_rows());
	for (unsigned int i = 0; i < m.get_rows(); i++) {
		double sum = 0;
		for (unsigned int k = 0; k < m.get_columns(); k++) {
			sum += m(i, k) * v(k);
		}
		new_vector(i) = sum;

	}
	return new_vector;
}
Vector operator*(Vector v, Matrix m) {
	v.transpose();
	m.transpose();
	return operator*(m, v);
}
Matrix operator*(Vector v1, Vector v2) {
	if (v2.get_size() != v1.get_size())
		throw std::runtime_error(
				"Error: Dimensions " + std::to_string(v1.get_size()) + " and "
						+ std::to_string(v2.get_size())
						+ " are not compatible with multiplication");
	if (!(v1.get_transposed() ^ v2.get_transposed()))
		throw std::runtime_error(
				"Error: Vector multiplication must have one get_transposed() vector");

	if ((v1.get_transposed() == 0) & (v2.get_transposed() == 1)) {
		Matrix m = Matrix(v1.get_size(), v2.get_size());
		for (unsigned int i = 0; i < v1.get_size(); i++)
			for (unsigned int j = 0; j < v2.get_size(); j++)
				m(i, j) = v1(i) * v2(j);

		return m;
	}
	Matrix m = Matrix(1, 1);
	for (unsigned int i = 0; i < v1.get_size(); i++)
		for (unsigned int j = 0; j < v2.get_size(); j++)
			m(1, 1) += v1(i) * v2(j);

	return m;

}
void Matrix::transpose() {
	transposed = true;

	unsigned int temp = rows;
	rows = columns;
	columns = temp;
}
Matrix transpose(Matrix m) {
	m.transpose();
	return m;
}
bool operator==(Matrix m1, Matrix m2) {
	for (unsigned int i = 0; i < m1.get_rows(); i++)
		for (unsigned int j = 0; j < m2.get_columns(); j++)
			if (m1(i, j) != m2(i, j))
				return false;
	return true;
}
double& Matrix::operator()(unsigned int row, unsigned int column) {
	//http://www.cplusplus.com/reference/string/to_string/
	//https://stackoverflow.com/questions/12261915/how-to-throw-stdexceptions-with-variable-messages
	if (row >= rows)
		throw std::runtime_error(
				"IndexError: " + std::to_string(row) + " >= "
						+ std::to_string(rows));
	if (column >= columns)
		throw std::runtime_error(
				"IndexError: " + std::to_string(column) + " >= "
						+ std::to_string(columns));
	if (transposed)
		return array[rows * column + row];
	return array[columns * row + column];
}
IdentityMatrix::IdentityMatrix(unsigned int size) :
		Matrix(size, size) {
	for (unsigned int i = 0; i < size; i++)
		(*this)(i, i) = 1;
}

Vector::Vector() {
	size = 0;
}
Vector Vector::operator=(Vector other) {
	transposed = other.transposed;
	array = other.array;
	size = other.size;
	return *this;
}

double& Vector::operator()(unsigned int index) {
	if (index >= get_size())
		throw std::runtime_error(
				"IndexError: " + std::to_string(index) + " >= "
						+ std::to_string(get_size()));
	return array[index];
}
void Vector::transpose() {
	transposed = ~transposed;
}
Vector transpose(Vector v) {
	v.transpose();
	return v;
}
Vector::Vector(unsigned int size) {
	transposed = false;
	this->size = size;

	array.resize(size);
	for (unsigned int i = 0; i < size; i++)
		array[i] = 0;
}
unsigned int Vector::get_size() const {
	return size;
}
bool Vector::get_transposed() const {
	return transposed;
}
void Vector::print() {
	char divider = '\n';
	if (transposed)
		divider = ' ';

	for (unsigned int i = 0; i < this->size; i++)
		std::cout << (*this)(i) << divider;
	if (transposed)
		std::cout << std::endl;
	std::cout << std::endl;
}
Vector operator+(Vector v1, Vector v2) {
	if (v1.get_transposed() ^ v2.get_transposed())
		throw std::runtime_error(
				"Error: A transposed and untransposed vector cannot  be added");
	for (unsigned int i = 0; i < v1.get_size(); i++)
		v1(i) += v2(i);
	return v1;
}
Vector operator-(Vector v1, Vector v2) {
	if (v1.get_transposed() ^ v2.get_transposed())
		throw std::runtime_error(
				"Error: A transposed and untransposed vector cannot  be subtracted");
	for (unsigned int i = 0; i < v1.get_size(); i++)
		v1(i) -= v2(i);
	return v1;
}
bool operator==(Vector v1, Vector v2) {
	for (unsigned int i = 0; i < v1.get_size(); i++)
		if (v1(i) != v2(i))
			return false;
	return true;
}
