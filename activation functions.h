#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_
#include "data types/Matrix.h"
#include <cmath>
class activation {
public:
	virtual Vector call(Vector v) {
		return v;
	}
	virtual Matrix call_derivative(Vector v) {
		return IdentityMatrix();
	}
};
class softmax: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class sigmoid: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
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
