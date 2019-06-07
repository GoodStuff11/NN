#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

#include "../data types/Tensor.h"
#include <string>

namespace af {
	Tensor softmax(Tensor v);
	Tensor sigmoid(Tensor v);
	Tensor softplus(Tensor v);
	Tensor tanh(Tensor v);
	Tensor relu(Tensor v);
	Tensor elu(Tensor v);
	Tensor leaky_relu(Tensor v);
	Tensor step(Tensor v);
	Tensor none(Tensor v);

	Tensor softmax_derivative(Tensor v);
	Tensor relu_derivative(Tensor v);
	Tensor sigmoid_derivative(Tensor v);
	Tensor step_derivative(Tensor v);
	Tensor none_derivative(Tensor v);
}

#endif /* ACTIVATION_FUNCTIONS_H_ */
