#include "Layer.h"
#include <iostream>
#include "activation functions.h"

unsigned int Layer::getNodes() const {
	return nodes;
}
void Layer::decodeActivationFunction(std::string function) {
	if(function == "softmax") {
		activation_function = &af::softmax;
		activation_function_derivative = &af::softmax_derivative;
	}
	else if(function == "sigmoid") {
		activation_function = &af::sigmoid;
		activation_function_derivative = &af::sigmoid_derivative;
	}
	else if(function == "softplus") {
		activation_function = &af::softplus;
	}
	else if(function == "tanh") {
		activation_function = &af::tanh;
	}
	else if(function == "relu") {
		activation_function = &af::relu;
		activation_function_derivative = &af::relu_derivative;
	}
	else if(function == "step") {
		activation_function = &af::step;
	}
	else if(function == "elu") {
		activation_function = &af::elu;
	}
	else if(function == "leaky relu") {
		activation_function = &af::leaky_relu;
	}
	else {
		activation_function = &af::none;
		activation_function_derivative = &af::none_derivative;
	}
}
dense::dense(unsigned int output) {
	activation_function = &af::none;
	activation_function_derivative = &af::none_derivative;
	nodes = output;
	biases = Vector(nodes);
}

dense::dense(unsigned int output_nodes, std::string function) {
	// activation functions that do not have a derivative are not yet implemented and aren't yet supported
	decodeActivationFunction(function);
	nodes = output_nodes;
	biases = Vector(nodes);
}
void dense::build(Layer* previous_layer) {
	unsigned int other_nodes = previous_layer->getNodes();
	if(other_nodes == 0)
		other_nodes = nodes;
	weights = Matrix(nodes, other_nodes);
}
Vector dense::call(Vector input) {
	return activation_function(weights * input + biases);
}
Vector Layer::calculate_s(Vector error, Vector nodes) const {
	std::cout << activation_function_derivative(nodes) << std::endl;
	return transpose(error) * activation_function_derivative(nodes);
}
Vector dense::update(Vector s, Vector nodes) {
	const double training_rate = 0.1;
	std::cout << s << "WATER" << std::endl;
	Vector new_s = transpose(s) * weights * activation_function_derivative(nodes);

	weights = weights - training_rate * s * transpose(nodes);
	biases = biases - training_rate * s;
	return new_s;
}
activation::activation(std::string function) {
	decodeActivationFunction(function);
	nodes = -1;
}
Vector activation::call(Vector input) {
	return activation_function(input);
}

