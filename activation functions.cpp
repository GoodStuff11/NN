#include "activation functions.h"

Vector softmax::call(Vector v) {
	double sum = 0;
	for (unsigned int i = 0; i < v.rows; i++)
		sum += exp(v(i));
	for (unsigned int i = 0; i < v.rows; i++)
		v(i) = exp(v(i)) * sum;
	return v;
}
Matrix softmax::call_derivative(Vector v) {
	Vector u = call(v);
	Matrix output = Matrix(u.rows, v.rows);
	for (int i = 0; i < u.rows; i++) {
		for (int j = 0; j < v.rows; j++) {
			if (i != j)
				output(i, j) = -u(i) * u(j);
			else
				output(i, i) = u(i) * (1 - u(i));
		}
	}
	return output;
}
Vector sigmoid::call(Vector v) {
	for (unsigned int i = 0; i < v.rows; i++)
		v(i) = 1 / (exp(-v(i)) + 1);
	return v;
}
Matrix sigmoid::call_derivative(Vector v) {
	return call(v) * (1 - v).transpose();
}
Vector softplus::call(Vector v) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++)
			v(i, j) = log(1 + exp(v(i, j)));
	return v;
}
Vector tanh::call(Vector v) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++)
			v(i, j) = tanh(v(i, j));
	return v;
}
Vector relu::call(Vector v) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++) {
			double val = v(i, j);
			if (val < 0)
				v(i, j) = 0;
			else
				v(i, j) = val;
		}
	return v;
}
Vector elu::call(Vector v, double a) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++) {
			double val = v(i, j);
			if (val < 0)
				v(i, j) = a * (exp(val) - 1);
			else
				v(i, j) = val;
		}
	return v;
}
Vector leaky_relu::call(Vector v, double a) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++) {
			double val = v(i, j);
			if (val < 0)
				v(i, j) = a * val;
			else
				v(i, j) = val;
		}
	return v;
}
Vector step::call(Vector v) {
	for (unsigned int i = 0; i < v.rows; i++)
		for (unsigned int j = 0; j < v.rows; j++) {
			if (v(i, j) < 0)
				v(i, j) = 0;
			else
				v(i, j) = 1;
		}
	return v;
}
Vector none::call(Vector v) {
	return v;
}
