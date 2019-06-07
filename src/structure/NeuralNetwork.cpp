#include "NeuralNetwork.h"
#include "loss functions.h"

NeuralNetwork::NeuralNetwork() {
	model = new list<Layer*>();
	loss_function = &MSE;
}
NeuralNetwork::~NeuralNetwork() {
	delete model;
}

void NeuralNetwork::add_layer(Layer* new_layer) {
	model->push_back(new_layer);
}
void NeuralNetwork::set_loss_function(std::string function) {
	if(function == "MSE")
		this->loss_function = &MSE;
	else if(function == "MAE")
		this->loss_function = &MAE;
}
Tensor NeuralNetwork::predict(Tensor input) {
	for(int i = 0; i < model->size(); i++) {
		cout << input << "\n\n";
		input = model->valAt(i)->call(input);
	}
	return input;
}
// same as predict but returns all node values
Tensor* NeuralNetwork::calculate_nodes(Tensor input) {
	Tensor* nodes = new Tensor[model->size()];

	for(int i = 0; i < model->size() - 1; i++) {
		nodes[i] = input;
		input = model->valAt(i + 1)->call(input);
		// next layer's weights do calculations
	}
	nodes[model->size() - 1] = input; // preventing array out of bounds
	return nodes;
}
void NeuralNetwork::build(std::string function) {
	set_loss_function(function);
	for(int layer = 1; layer < model->size(); layer++) {
		model->valAt(layer)->build(model->valAt(layer - 1));
	}
}
// TODO: implement batch size and a return value so that progress can be plotted
// for each row, I adjusted the weights. I did NOT take the average and adjust them with that
void NeuralNetwork::fit(DataFrame& train_data, DataFrame& train_labels, unsigned int epochs) {
	// a row in train_data and train_labels are the input and output Tensors respectively
	for(unsigned int i = 0; i < epochs; i++) {
		for(unsigned int row = 0; row < train_data.get_rows(); row++) {
			unsigned int size = model->size();

			//Tensor output = predict(array2Tensor(train_data[row], train_data.get_columns()));
			Tensor* nodes = calculate_nodes(array2Tensor(train_data[row], train_data.get_columns()));
			Tensor expected_output = array2Tensor(train_labels[row], train_labels.get_columns());
			Tensor error = loss_function(nodes[size - 1], expected_output);

			Tensor s = model->valAt(size - 1)->calculate_s(error, nodes[size - 1]);

			for(int layer_number = size - 2; layer_number > 0; layer_number--) {
				Layer* current_layer = model->valAt(layer_number);
				s = current_layer->update(s, nodes[layer_number - 1]);
			}
		}
	}
}
