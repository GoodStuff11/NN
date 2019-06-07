#include "data types/DataFrame.h"
#include "structure/NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	//csv2binary("training_labels.txt");
	DataFrame *training = read_binary_file("../data/training.bin");
	DataFrame *training_labels = read_binary_file("../data/training_labels.bin");

	NeuralNetwork *model = new NeuralNetwork();
	model->add_layer(new input(2));
	model->add_layer(new dense(2, "relu"));
	model->add_layer(new dense(1, "relu"));
	
	model->build("MSE");
	model->fit(*training,*training_labels,3);
	model->set_loss_function("step"); // guaranteed to settle on an answer
/*
	cout << model->predict({0,0}) << endl;
	cout << model->predict({1,0}) << endl;
	cout << model->predict({0,1}) << endl;
	cout << model->predict({1,1}) << endl;
	*/
	return 0;
}
