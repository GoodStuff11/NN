#include "data types/DataFrame.h"
#include "structure/NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

int main() {

	csv2binary("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training.csv");
	csv2binary("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training_labels.csv");
	DataFrame* training = read_binary_file("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training.bin");
	DataFrame* training_labels = read_binary_file("C:/Users/htpc/Source/Repos/GoodStuff11/Neural-Network/data/training_labels.bin");

	srand(time(NULL));
	//cout << training << endl << training_labels << endl;

	NeuralNetwork* model = new NeuralNetwork(0.01);
	model->add_layer(new input(2));
	model->add_layer(new dense(1));

	model->build("MSE");
	
	model->fit(*training, *training_labels, 100, 1);
	cout << model->predict({ -0.5,1 });
	return 0;
}
