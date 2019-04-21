#include "NeuralNetwork.h"
#include "loss functions.h"

NeuralNetwork::NeuralNetwork() {
	model = new list<layer*>();
	loss_function = MSE;
}
NeuralNetwork::~NeuralNetwork() {
	delete model;
}

void NeuralNetwork::add_layer(layer *new_layer) {
	model->push_back(new_layer);
}
void NeuralNetwork::set_loss_function(double loss_function(Matrix*, Matrix*)) {
	this->loss_function = loss_function;
}
