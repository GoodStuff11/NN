#include "activation functions.h"
#include <cmath>
#include <iostream>
namespace af {
	Vector softmax(Vector v) {
		double sum = 0;
		for(unsigned int i = 0; i < v.get_size(); i++)
			sum += exp(v(i));
		for(unsigned int i = 0; i < v.get_size(); i++)
			v(i) = exp(v(i)) * sum;
		return v;
	}
	Vector sigmoid(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++)
			v(i) = 1 / (exp(-v(i)) + 1);
		return v;
	}
	Vector softplus(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++)
			v(i) = log(1 + exp(v(i)));
		return v;
	}
	Vector tanh(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++)
			v(i) = std::tanh(v(i));
		return v;
	}
	Vector relu(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++) {
			double val = v(i);
			if(val < 0)
				v(i) = 0;
			else
				v(i) = val;
		}
		return v;
	}
	Vector elu(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++) {
			double val = v(i);
			if(val < 0)
				v(i) = 0.5 * (exp(val) - 1);
			else
				v(i) = val;
		}
		return v;
	}
	Vector leaky_relu(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++) {
			double val = v(i);
			if(val < 0)
				v(i) = 0.5 * val;
			else
				v(i) = val;
		}
		return v;
	}
	Vector step(Vector v) {
		for(unsigned int i = 0; i < v.get_size(); i++) {
			if(v(i) < 0)
				v(i) = 0;
			else
				v(i) = 1;
		}
		return v;
	}
	Vector none(Vector v) {
		return v;
	}

	Matrix softmax_derivative(Vector v) {
		Vector u = softmax(v);
		Matrix output = Matrix(u.get_size(), v.get_size());
		for(unsigned int i = 0; i < u.get_size(); i++) {
			for(unsigned int j = 0; j < v.get_size(); j++) {
				if(i != j)
					output(i, j) = -u(i) * u(j);
				else
					output(i, i) = u(i) * (1 - u(i));
			}
		}
		return output;
	}
	Matrix relu_derivative(Vector v) {
		Matrix m = IdentityMatrix(v.get_size());
		for(unsigned int i = 0; i < v.get_size(); i++) {
			if(v(i) > 0)
				m(i, i) = 1;
			else
				m(i, i) = 0;
		}
		return m;
	}
	Matrix step_derivative(Vector v) {
		// it's better to not use this function for optimization
		return Matrix(v.get_size(), v.get_size());
	}
	Matrix sigmoid_derivative(Vector v) {
		return sigmoid(v) * transpose(1 - v);
	}
	Matrix none_derivative(Vector v) {
		return IdentityMatrix(v.get_size());
	}

}
