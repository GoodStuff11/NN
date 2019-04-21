#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix{
private:
	double* matrix;
public:
	unsigned int rows;
	unsigned int columns;

	Matrix(unsigned int rows, unsigned int columns);
	virtual ~Matrix();

	double& operator()(unsigned int row,unsigned int column);
	Matrix* operator+(Matrix other);
	Matrix* operator*(Matrix other);
	Matrix* operator-(Matrix other);

	void print();
};

#endif
