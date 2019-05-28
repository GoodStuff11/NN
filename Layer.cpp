#include "activation functions.h"
#include "Layers.h"

unsigned int Layer::getNotes() const{
	return nodes;	
}
void Layer::decodeActivationFunction(std::string function){
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
}
dense::dense(unsigned int output) {
	activation_function = &none;
	activation_function_derivative = &none_derivative;
	nodes = output;
}

dense::dense(unsigned int output_nodes, std::string function) {
	// activation functions that do not have a derivative are not yet implemented and aren't yet supported
	decodeActivationFunction(function);
	nodes = output_nodes;
}
dense::build(Layer *previous_layer){
	unsigned int other_nodes = previous_layer->getNodes();
	if (other_nodes == -1)
		other_nodes = nodes;
	transform = Matrix(other_nodes, nodes);
}
Vector dense::call(Vector input) const {
	return activation_function(transform * input);
}
Matrix dense::update(Vector s, Vector nodes) {
	const double training_rate = 0.1;
	
	Vector new_s = transpose(s) * transform * activation_function_derivative(nodes);
	transform = transform - training_rate * s * transpose(nodes);
	
	return new_s;
}
activation::activation(std::string function){
	decodeActivationFunction(function);
	nodes = -1;
}
void activation::call(Vector input){
	return activation_function(input);
}
Matrix update(Vector s, Vector nodes){
	return IdentityMatrix(); // I don't know what to return here yet	
}
void build(Layer *previous_layer){

}

