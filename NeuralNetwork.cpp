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
// TODO: implement batch size and a return value so that progress can be plotted
// for each row, I adjusted the weights. I did NOT take the average and adjust them with that
void NeuralNetwork::fit(DataFrame train_data, DataFrame train_labels, unsigned int epochs) {
	// a row in train_data and train_labels are the input and output vectors respectively
	for (unsigned int i = 0; i < epochs; i++){
		for (int row = 0; row < train_data.get_rows(); row++) {
			//Vector output = predict(array2vector(train_data[row], train_data.get_columns()));
			Vector *nodes = calculate_nodes(array2vector(train_data[row], train_data.get_columns()));
			Vector expected_output = array2vector(train_labels[row],train_data.get_columns());
			Vector error = loss_function(nodes[0], expected_output);

			Vector s = model->valAt(layer_number).calculate_s(error, nodes[0]);
			for (int layer_number = 1; layer_number < model->size() - 1;layer_number++) {
				Layer current_layer = model->valAt(layer_number);
				s = current_layer.update(s, nodes[layer_number]);
			}
		}
	}
}
