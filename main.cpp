#include "data types/DataFrame.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>
#include "data types/Matrix.h"

using namespace std;

int rand(int min, int max) {
	//return min <= x < max
	return rand() % (max - min) + min;
}
int main() {

	int size = 10;
	DataFrame *df = new DataFrame(size, size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*df)(i, j) = rand(0, 100);
	df->print();
	cout << endl;

	df->sort_by(0);
	df->print();
	cout << endl;

	NeuralNetwork *model = new NeuralNetwork();
	model->add_layer(new dense(2, 2, "relu"));
	model->add_layer(new dense(2, 1, "softmax"));

	Vector v = Vector(2);
	v(0) = 1;
	v(1) = 2;
	model->predict(v).print();

	return 0;
}
