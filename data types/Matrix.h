#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>
class MatrixStructure{
public:
	protected std::vector<double> array;
	protected unsigned int rows;
	protected unsigned int columns;

	MatrixStructure operator+(MatrixStructure other);
	MatrixStructure operator*(MatrixStructure other);
	MatrixStructure operator-(MatrixStructure other);
	MatrixStructure operator=(MatrixStructure other);
	MatrixStructure operator==(MatrixStructure other);
	MatrixStructure transpose();
	void print();
}
class Matrix: public MatrixStructure{
private:
	std::vector<double> matrix;
public:
	Matrix();
	Matrix(unsigned int rows, unsigned int columns);
	
	int get_rows();
	int get_columns();
	double& operator()(unsigned int row, unsigned int column);
};

//https://stackoverflow.com/questions/120876/what-are-the-rules-for-calling-the-superclass-constructor
class IdentityMatrix: public Matrix {
public:
	IdentityMatrix(unsigned int size);
};
class Vector: public MatrixStructure {
public:
	Vector();
	Vector(unsigned int size);
	
	int get_size();
	double& operator()(unsigned int index);
};

#endif
