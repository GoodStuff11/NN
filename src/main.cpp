#include "data types/DataFrame.h"
#include "structure/NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

int main() {
	
	csv2binary("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training2.csv");
	csv2binary("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training_labels2.csv");
	DataFrame* training = read_binary_file("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training2.bin");
	DataFrame* training_labels = read_binary_file("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training_labels2.bin");

	srand(time(NULL));
	//cout << training << endl << training_labels << endl;

	NeuralNetwork* model = new NeuralNetwork(0.3);
	model->add_layer(new input(2));
	model->add_layer(new dense(1));
	//model->add_layer(new dense(1, "relu"));

	model->build("MSE");
	
	/*
	model->layers->valAt(1)->set_weights(Tensor({1,-1,-1,1}).reshape({2,2}));
	model->layers->valAt(2)->set_weights(Tensor({1,1}).reshape({1,2}));
	model->layers->valAt(1)->set_biases(Tensor({0,0}));
	model->layers->valAt(2)->set_biases(Tensor({0}));
	*/
	model->fit(*training,*training_labels,15);
	//model->layers->valAt(2)->set_activation_function("step");
	/*
	cout << "-----------------------------" << endl;
	cout << model->predict({0,0}) << endl;
	cout << model->predict({1,0}) << endl;
	cout << model->predict({0,1}) << endl;
	cout << model->predict({1,1}) << endl;
	*/
	//cout << model->predict({0,0}) << endl;
	
	return 0;
}
