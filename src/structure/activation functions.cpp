#include "activation functions.h"
#include <cmath>
#include <iostream>
namespace af {
	Tensor softmax(Tensor v) {
		double sum = 0;
		for(unsigned int i = 0; i < v.get_dim(0); i++)
			sum += exp(v({i}));
		for(unsigned int i = 0; i < v.get_dim(0); i++)
			v({i}) = exp(v({i})) * sum;
		return v;
	}
	Tensor sigmoid(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++)
			v({i}) = 1 / (exp(-v({i})) + 1);
		return v;
	}
	Tensor softplus(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++)
			v({i}) = log(1 + exp(v({i})));
		return v;
	}
	Tensor tanh(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++)
			v({i}) = std::tanh(v({i}));
		return v;
	}
	Tensor relu(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			double val = v({i});
			if(val < 0)
				v({i}) = 0;
			else
				v({i}) = val;
		}
		return v;
	}
	Tensor elu(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			double val = v({i});
			if(val < 0)
				v({i}) = 0.5 * (exp(val) - 1);
			else
				v({i}) = val;
		}
		return v;
	}
	Tensor leaky_relu(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			double val = v({i});
			if(val < 0)
				v({i}) = 0.5 * val;
			else
				v({i}) = val;
		}
		return v;
	}
	Tensor step(Tensor v) {
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			if(v({i}) < 0)
				v({i}) = 0;
			else
				v({i}) = 1;
		}
		return v;
	}
	Tensor none(Tensor v) {
		return v;
	}

	Tensor softmax_derivative(Tensor v) {
		Tensor u = softmax(v);
		Tensor output = EmptyTensor({v.get_dim(0), v.get_dim(0)});
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			for(unsigned int j = 0; j < v.get_dim(0); j++) {
				if(i != j)
					output({i, j}) = -u({i}) * u({j});
				else
					output({i, i}) = u({i}) * (1 - u({i}));
			}
		}
		return output;
	}
	Tensor relu_derivative(Tensor v) {
		Tensor m = EmptyTensor({v.get_dim(0),v.get_dim(0)});
		for(unsigned int i = 0; i < v.get_dim(0); i++) {
			if(v({i}) >= 0)
				m({i, i}) = 1;
			else
				m({i, i}) = 0;
		}
		return m;
	}
	Tensor step_derivative(Tensor v) {
		// it's better to not use this function for optimization
		return EmptyTensor({v.get_dim(0), v.get_dim(0)});
	}
	Tensor sigmoid_derivative(Tensor v) {
		return tensor_product(sigmoid(v), 1 - v);
	}
	Tensor none_derivative(Tensor v) {
		return EmptyTensor({v.get_dim(0),v.get_dim(0)});
	}

}
