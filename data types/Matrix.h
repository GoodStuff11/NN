#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>
class MatrixStructure{
protected:
	std::vector<double> array;
	unsigned int rows;
	unsigned int columns;
	bool transposed;

	double& operator()(unsigned int row, unsigned int column);
	MatrixStructure(unsigned int rows, unsigned int columns);
	MatrixStructure();
public:

	MatrixStructure operator+(MatrixStructure other);
	MatrixStructure operator*(MatrixStructure other);
	MatrixStructure operator-(MatrixStructure other);
	MatrixStructure operator==(MatrixStructure other);
	MatrixStructure transpose();
	void print();
};
class Matrix: public MatrixStructure{
public:
	//https://stackoverflow.com/questions/2986891/how-to-publicly-inherit-from-a-base-class-but-make-some-of-public-methods-from-t

	Matrix();
	Matrix(unsigned int rows, unsigned int columns);

	unsigned int get_rows();
	unsigned int get_columns();

	Matrix operator=(MatrixStructure other);
	//double& operator()(unsigned int row, unsigned int column);
	using MatrixStructure::operator();
};

//https://stackoverflow.com/questions/120876/what-are-the-rules-for-calling-the-superclass-constructor
class IdentityMatrix: public Matrix {
public:
	IdentityMatrix(unsigned int size);
};

class Vector: public MatrixStructure {
protected:
	double& operator()(unsigned int row, unsigned int column);
public:
	Vector();
	Vector(unsigned int size);

	Vector operator=(MatrixStructure other);
	unsigned int get_size();
	double& operator()(unsigned int index);
};

#endif
