#include "layers.h"
#include "activation functions.cpp"

dense::dense(int input, int output) {
	activation = none;
	transform = new Matrix(input, output);
}
dense::dense(int input, int output, void activation(Matrix*)) {
	this->activation = activation;
	transform = new Matrix(input, output);
}
void dense::apply(Matrix* input) {
	input = transform * input;
	activation(input);
}

