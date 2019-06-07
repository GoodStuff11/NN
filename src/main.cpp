#include "data types/DataFrame.h"
#include "structure/NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>
#include "data types/Matrix.h"

using namespace std;

int rand(int min, int max) {
	//return min <= x < max
	return rand() % (max - min) + min;
}
int main() {
	//csv2binary("training_labels.txt");
	DataFrame *training = new DataFrame();
	DataFrame *training_labels = new DataFrame();

	training->read_binary_file("training.bin");
	training_labels->read_binary_file("training_labels.bin");

	cout << training << endl;
	cout << training_labels << endl;

/*
	int size = 10;
	DataFrame *df = new DataFrame(size, size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*df)(i, j) = rand(0, 100);
	df->print();
	cout << endl;

	NeuralNetwork *model = new NeuralNetwork();
	model->add_layer(new dense(2, 2, "relu"));
	model->add_layer(new dense(2, 1, "softmax"));

	model->fit()
*/
	return 0;
}
