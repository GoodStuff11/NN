#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

#include "data types/Matrix.h"
class activation {
public:
	virtual Vector call(Vector v) {
		return v;
	}
	virtual Matrix call_derivative(Vector v) {
		return IdentityMatrix(v.get_size());
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
class relu: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class leaky_relu: public activation {
public:
	//assume a = 0.5
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class tanh: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class elu: public activation {
public:
	//assume a = 0.5
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class step: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class softplus: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};
class none: public activation {
public:
	Vector call(Vector v);
	Matrix call_derivative(Vector v);
};

#endif /* ACTIVATION_FUNCTIONS_H_ */
