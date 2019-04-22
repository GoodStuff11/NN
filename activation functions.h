#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_
#include "data types/Matrix.h"
#include <cmath>
class activation {
public:
	virtual Matrix call(Matrix mat) {
		return mat;
	}
	virtual Matrix call_derivative(Matrix mat) {
		return Matrix(mat.rows, mat.columns);
	}
};
class softmax: public activation {
public:
	Matrix call(Matrix mat);
	Matrix call_derivative(Matrix mat);
};
class sigmoid: public activation {
public:
	Matrix call(Matrix mat);
	Matrix call_derivative(Matrix mat);
};

Matrix softmax(Matrix mat);
Matrix sigmoid(Matrix mat);
Matrix relu(Matrix mat);
Matrix leaky_relu(Matrix mat, double a);
Matrix tanh(Matrix mat);
Matrix elu(Matrix mat, double a);
Matrix step(Matrix mat);
Matrix softplus(Matrix mat);
Matrix none(Matrix mat);

#endif /* ACTIVATION_FUNCTIONS_H_ */
