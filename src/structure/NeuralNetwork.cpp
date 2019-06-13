#include "NeuralNetwork.h"
#include "loss functions.h"
#include <fstream>
using namespace std;

NeuralNetwork::NeuralNetwork() {
	layers = new list<Layer*>();
	loss_function = &MSE;
	training_rate = 0.5;
}
NeuralNetwork::NeuralNetwork(double training_rate) {
	layers = new list<Layer*>();
	loss_function = &MSE;
	this->training_rate = training_rate;
}
NeuralNetwork::~NeuralNetwork() {
	delete layers;
}

void NeuralNetwork::add_layer(Layer* new_layer) {
	new_layer->training_rate = training_rate;
	layers->push_back(new_layer);

}
void NeuralNetwork::set_loss_function(std::string function) {
	if(function == "MSE")
		this->loss_function = &MSE;
	else if(function == "MAE")
		this->loss_function = &MAE;
}
Tensor NeuralNetwork::predict(Tensor input) {
	//cout << "PREDICT:" << endl;
	for(int i = 1; i < layers->size(); i++) {
		//cout << input << endl;
		input = layers->valAt(i)->call(input);
	}
	return input;
}
// same as predict but returns all node values
Tensor* NeuralNetwork::calculate_nodes(Tensor input) {
	Tensor* nodes = new Tensor[layers->size()];

	for(int i = 0; i < layers->size() - 1; i++) {
		nodes[i] = input;
		input = layers->valAt(i + 1)->call(input);
		// next layer's weights do calculations
	}
	nodes[layers->size() - 1] = input; // preventing array out of bounds
	return nodes;
}
void NeuralNetwork::build(std::string function) {
	set_loss_function(function);
	for(int layer = 1; layer < layers->size(); layer++) {
		layers->valAt(layer)->build(layers->valAt(layer - 1));
	}
}
// TODO: implement batch size and a return value so that progress can be plotted
// for each row, I adjusted the weights. I did NOT take the average and adjust them with that
void NeuralNetwork::fit(DataFrame& train_data, DataFrame& train_labels, unsigned int epochs) {
	// a row in train_data and train_labels are the input and output Tensors respectively
	ofstream file("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/src/fit output.txt");
	for(unsigned int i = 0; i < epochs; i++) {
		for(unsigned int row = 0; row < train_data.get_rows(); row++) {
			unsigned int size = layers->size();

			Tensor* nodes = calculate_nodes(array2Tensor(train_data[row], train_data.get_columns()));
			Tensor expected_output = array2Tensor(train_labels[row], train_labels.get_columns());
			Tensor error = loss_function(nodes[size - 1], expected_output);
			file << error;
			cout << error;
			Tensor s = layers->valAt(size - 1)->calculate_s(error, nodes[size - 1]);
			
			for(int layer_number = size - 1; layer_number > 0; layer_number--) {

				Layer* current_layer = layers->valAt(layer_number);
				s = current_layer->update(s, nodes[layer_number - 1]);
			}
		}
	}
	file.close();
}
void NeuralNetwork::set_training_rate(double rate) {
	training_rate = rate;
	for(int i = 0; i < layers->size(); i++) {
		layers->valAt(i)->training_rate = rate;
	}
}