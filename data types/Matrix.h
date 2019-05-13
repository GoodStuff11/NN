#ifndef MATRIX_H_
#define MATRIX_H_
#include <vector>

class Vector {
private:
	std::vector<double> array;
	unsigned int size;
	bool transposed;
public:
	Vector();
	Vector(unsigned int size);

	Vector operator=(Vector other);
	unsigned int get_size() const;
	double& operator()(unsigned int index);
	friend Vector transpose(Vector v);
	bool get_transposed() const;

	void transpose();
	void print();
};

class Matrix {
protected:
	//https://stackoverflow.com/questions/2986891/how-to-publicly-inherit-from-a-base-class-but-make-some-of-public-methods-from-t
	std::vector<double> array;
	unsigned int rows;
	unsigned int columns;
	bool transposed;
public:
	double& operator()(unsigned int row, unsigned int column);

	Matrix();
	Matrix(unsigned int rows, unsigned int columns);

	unsigned int get_rows() const;
	unsigned int get_columns() const;
	friend Matrix transpose(Matrix m);
	void transpose();
	void print();

	Matrix operator=(Matrix other);

};

//https://stackoverflow.com/questions/120876/what-are-the-rules-for-calling-the-superclass-constructor
class IdentityMatrix: public Matrix {
public:
	IdentityMatrix(unsigned int size);
};
Vector array2vector(double* array, int size);

Matrix operator+(Matrix m1, Matrix m2);
Vector operator+(Vector m1, Vector m2);

Vector operator-(Vector m1, Vector m2);
Matrix operator-(Matrix m1, Matrix m2);

bool operator==(Matrix m1, Matrix m2);
bool operator==(Vector m1, Vector m2);


Matrix operator*(Matrix m1, Matrix m2);
Vector operator*(Vector v, Matrix m);
Vector operator*(Matrix m, Vector v);
Matrix operator*(Vector m, Vector v);

Matrix operator*(double constant, Matrix m);
Vector operator*(double constant, Vector m);
Vector operator+(double constant, Vector m);
Vector operator-(double constant, Vector m);
Vector operator+(Vector m, double constant);
Vector operator-(Vector m, double constant);
#endif
