#include "NeuralNetwork.h"
#include "loss functions.h"

NeuralNetwork::NeuralNetwork() {
	model = new list<layer*>();
	loss_function = &MSE;
}
NeuralNetwork::~NeuralNetwork() {
	delete model;
}

void NeuralNetwork::add_layer(layer *new_layer) {
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
void NeuralNetwork::fit(DataFrame train_data, DataFrame train_labels) {
	// a row in train_data and train_labels are the input and output vectors respectively
	for (int row = 0; row < train_data.get_rows(); row++) {
		Vector v = array2vector(train_data[row],train_data.get_columns());
	}
}
