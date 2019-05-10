#include "loss functions.h"
#include <cmath>
using namespace std;

Vector MSE(Vector input, Vector expected) {
	/*
	 double MS = 0;
	 for (unsigned int i = 0; i < input.rows; i++) {
	 for (unsigned int j = 0; j < input.columns; j++) {
	 MS += pow(input(i, j) - expected(i, j), 2);
	 }
	 }
	 return MS / (input.rows * input.columns);
	 */
	//the only time this function will be used is for its derivative
	//so this function returns the derivative of the MSE
	return input - expected;
}
Vector MAE(Vector input, Vector expected) {
	double MS = 0;
	for (unsigned int i = 0; i < input.get_size(); i++) {
		MS += abs(input(i) - expected(i));
	}

	return MS / (input.get_size());
}
