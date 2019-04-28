#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>

class Matrix {
private:
	std::vector<double> matrix;
public:
	unsigned int rows;
	unsigned int columns;

	Matrix();
	Matrix(unsigned int rows, unsigned int columns);

	double& operator()(unsigned int row, unsigned int column);
	double& operator()(unsigned int row);
	Matrix operator+(Matrix other);
	Matrix operator*(Matrix other);
	Matrix operator-(Matrix other);
	Matrix operator=(Matrix other);
	Matrix transpose();
	void print();
};

//https://stackoverflow.com/questions/120876/what-are-the-rules-for-calling-the-superclass-constructor
class IdentityMatrix: public Matrix {
public:
	IdentityMatrix(unsigned int size);
};
class Vector: public Matrix {
public:
	Vector(unsigned int size);
};

#endif
