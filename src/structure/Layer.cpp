#include "Layer.h"
#include <iostream>
#include "activation functions.h"

using namespace std;

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
	biases = EmptyTensor({nodes});
	for(unsigned int i = 0; i < biases.get_dim(0); i++) 
		biases({i}) = ((double) rand() / (RAND_MAX));
}

dense::dense(unsigned int output_nodes, std::string function) {
	// activation functions that do not have a derivative are not yet implemented and aren't yet supported
	decodeActivationFunction(function);
	nodes = output_nodes;
	biases = EmptyTensor({nodes}); 
	for(unsigned int i = 0; i < biases.get_dim(0); i++) 
		biases({i}) = ((double) rand() / (RAND_MAX));
	
}
void dense::build(Layer* previous_layer) {
	unsigned int other_nodes = previous_layer->getNodes();
	if(other_nodes == 0)
		other_nodes = nodes;
	weights = EmptyTensor({nodes * other_nodes});
	for (int i = 0; i < weights.get_dim(0); i++)
		weights({i}) = ((double) rand() / (RAND_MAX));
	weights.reshape({nodes, other_nodes});
}
Tensor dense::call(Tensor input) {
	return activation_function(dot(weights, input) + biases);
}
Tensor Layer::calculate_s(Tensor error, Tensor nodes) const {
	return dot(error, activation_function_derivative(nodes));
}
Tensor dense::update(Tensor s, Tensor nodes) {
	Tensor new_s = dot(s, dot(weights, activation_function_derivative(nodes)));
	weights = weights - training_rate * tensor_product(s, nodes);
	biases = biases - training_rate * s;
	return new_s;
}
activation::activation(std::string function) {
	decodeActivationFunction(function);
	nodes = -1;
}
Tensor activation::call(Tensor input) {
	return activation_function(input);
}

