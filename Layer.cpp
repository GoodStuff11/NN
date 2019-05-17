#include "activation functions.h"
#include "Layers.h"
Layer::Layer() {
	activation_function = &af::none;
}
Vector Layer::apply(Vector input) {
	return input;
}
dense::dense(unsigned int input, unsigned int output) {
	transform = Matrix(input, output);
}
dense::dense(unsigned int input, unsigned int output, std::string function) {
	// activation functions that do not have a derivative are not yet implemented and aren't yet supported
	if (function == "softmax") {
		activation_function = &af::softmax;
		activation_function_derivative = &af::softmax_derivative;
	} else if (function == "sigmoid") {
		activation_function = &af::sigmoid;
		activation_function_derivative = &af::sigmoid_derivative;
	} else if (function == "softplus") {
		activation_function = &af::softplus;
	} else if (function == "tanh") {
		activation_function = &af::tanh;
	} else if (function == "relu") {
		activation_function = &af::relu;
		activation_function_derivative = &af::relu_derivative;
	} else if (function == "step") {
		activation_function = &af::step;
	} else if (function == "elu") {
		activation_function = &af::elu;
	} else if (function == "leaky relu") {
		activation_function = &af::leaky_relu;
	}
	transform = Matrix(input, output);
}
Vector dense::apply(Vector input) {
	return activation_function(transform * input);
}
void dense::update(Matrix deltaW) {
	transform = transform + deltaW;
}
