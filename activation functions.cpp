#include "activation functions.h"
#include <cmath>
Vector softmax::call(Vector v) {
	double sum = 0;
	for (unsigned int i = 0; i < v.get_size(); i++)
		sum += exp(v(i));
	for (unsigned int i = 0; i < v.get_size(); i++)
		v(i) = exp(v(i)) * sum;
	return v;
}
Matrix softmax::call_derivative(Vector v) {
	Vector u = call(v);
	Matrix output = Matrix(u.get_size(), v.get_size());
	for (int i = 0; i < u.get_size(); i++) {
		for (int j = 0; j < v.get_size(); j++) {
			if (i != j)
				output(i, j) = -u(i) * u(j);
			else
				output(i, i) = u(i) * (1 - u(i));
		}
	}
	return output;
}
Vector sigmoid::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++)
		v(i) = 1 / (exp(-v(i)) + 1);
	return v;
}
Matrix sigmoid::call_derivative(Vector v) {
	return call(v) * (1 - v).transpose();
}
Vector softplus::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++)
		v(i) = log(1 + exp(v(i)));
	return v;
}
Vector tanh::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++)
		v(i) = tanh(v(i));
	return v;
}
Vector relu::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++) {
		double val = v(i);
		if (val < 0)
			v(i) = 0;
		else
			v(i) = val;
	}
	return v;
}
Vector elu::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++) {
		double val = v(i);
		if (val < 0)
			v(i) = 0.5 * (exp(val) - 1);
		else
			v(i) = val;
	}
	return v;
}
Vector leaky_relu::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++) {
		double val = v(i);
		if (val < 0)
			v(i) = 0.5 * val;
		else
			v(i) = val;
	}
	return v;
}
Vector step::call(Vector v) {
	for (unsigned int i = 0; i < v.get_size(); i++) {
		if (v(i) < 0)
			v(i) = 0;
		else
			v(i) = 1;
	}
	return v;
}
Vector none::call(Vector v) {
	return v;
}
