#include "layers.h"
#include "activation functions.h"

layer::layer(){
	activation = &none;
}
Matrix layer::apply(Matrix input) {
	return input;
}
dense::dense(unsigned int input,unsigned int output) {
	transform = Matrix(input, output);
}
dense::dense(unsigned int input,unsigned int output, Matrix (*activation)(Matrix)) {
	this->activation = activation;
	transform = Matrix(input, output);
}
Matrix dense::apply(Matrix input) {
	return activation(transform*input);
}

