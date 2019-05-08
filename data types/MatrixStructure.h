#ifndef DATA_TYPES_MATRIXSTRUCTURE_H_
#define DATA_TYPES_MATRIXSTRUCTURE_H_

#include <vector>

class MatrixStructure {
	friend class Vector;
	friend class Matrix;
protected:
	std::vector<double> array;
	unsigned int rows;
	unsigned int columns;
	bool transposed;

	double& operator()(unsigned int row, unsigned int column);
	MatrixStructure(unsigned int rows, unsigned int columns);
	MatrixStructure();
public:

	friend MatrixStructure operator+(MatrixStructure m1,MatrixStructure m2);
	friend MatrixStructure operator*(MatrixStructure m1,MatrixStructure m2);
	friend MatrixStructure operator-(MatrixStructure m1,MatrixStructure m2);
	friend MatrixStructure operator==(MatrixStructure m1,MatrixStructure m2);

	friend MatrixStructure operator*(double constant,MatrixStructure m);
	friend MatrixStructure operator*(MatrixStructure m,double constant);

	friend MatrixStructure transpose(MatrixStructure m);

	void transpose();
	void print();
};

#endif /* DATA_TYPES_MATRIXSTRUCTURE_H_ */
