#include "data types/DataFrame.h"
#include "data types/Matrix.h"
//#include "NeuralNetwork.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int rand(int min, int max) {
	//return min <= x < max
	return rand() % (max - min) + min;
}
int main() {
	/*
	int size = 10;
	DataFrame *df = new DataFrame(size,size);

	for (int i = 0;i<size;i++)
		for (int j=0;j<size;j++)
			(*df)(i,j) = rand(0,100);
	df->print();
	cout << endl;

	df->sort_by(0);
	df->print();
	cout << endl;

	NeuralNetwork *model = new NeuralNetwork();
	model->add_layer(new dense(2,2,relu));
	model->add_layer(new dense(2,1,softmax));

	Matrix m = Matrix(2,1);
	m(0)=1;
	m(1)=2;
	model->predict(m).print();
	cout << endl;
*/
	Matrix mat = Matrix(3,3);
	mat(0,1) = 1;
	mat(1,0) = 1;
	mat(2,2) = 1;
	mat.print();

	cout<< endl;

	Vector v = Vector(3);
	v(0) = 2;
	v(1) = 3;
	v(2) = 8;
	v.print();

	cout << endl;
	v = mat*v;
	v.transpose().print();
	return 0;
}
