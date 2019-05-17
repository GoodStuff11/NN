#include "NeuralNetwork.h"
#include "loss functions.h"

NeuralNetwork::NeuralNetwork() {
	model = new list<Layer*>();
	loss_function = &MSE;
}
NeuralNetwork::~NeuralNetwork() {
	delete model;
}

void NeuralNetwork::add_layer(Layer *new_layer) {
	model->push_back(new_layer);
}
void NeuralNetwork::set_loss_function(std::string function) {
	if (function == "MSE")
		this->loss_function = &MSE;
	else if (function == "MAE")
		this->loss_function = &MAE;
}
Vector NeuralNetwork::predict(Vector input) {
	for (int i = 0; i < model->size(); i++) {
		input.print();
		cout << endl;
		input = model->valAt(i)->apply(input);
	}
	return input;
}
// same as predict but returns all node values
Vector* NeuralNetwork::calculate_nodes(Vector input) {
	Vector* nodes = new Vector[model->size()+1];
	for (int i = 0; i < model->size(); i++) {
		nodes[model->size()-i] = input;
		input = model->valAt(i)->apply(input);
	}
	nodes[0] = input;
	return nodes;
}
void NeuralNetwork::fit(DataFrame train_data, DataFrame train_labels) {
	// a row in train_data and train_labels are the input and output vectors respectively
	Vector *s = new Vector[model->size() - 1];
	for (int row = 0; row < train_data.get_rows(); row++) {
		Vector output = predict(array2vector(train_data[row], train_data.get_columns()));
		Vector expected_output = array2vector(train_labels[row],train_data.get_columns());
		Vector dEdu = loss_function(output, expected_output);

		for (int layer_number = 0; layer_number < model->size();layer_number++) {
			Layer current_layer = model->valAt(layer_number);
			s[layer_number] = current_layer.activation_function_derivative(current_nodes);
		}

	}
}
