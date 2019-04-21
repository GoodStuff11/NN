#include "loss functions.h"
#include <cmath>
using namespace std;

double MSE(Matrix *input, Matrix *expected) {
	double MS = 0;
	for (int i = 0; i < input->rows; i++) {
		for (int j = 0; j < input->columns; j++) {
			MS += pow((*input)(i, j) - (*expected)(i, j), 2);
		}
	}
	return MS / (input->rows * input->columns);
}
double MAE(Matrix *input, Matrix *expected) {
	double MS = 0;
	for (int i = 0; i < input->rows; i++) {
		for (int j = 0; j < input->columns; j++) {
			MS += abs((*input)(i, j) - (*expected)(i, j));
		}
	}
	return MS / (input->rows * input->columns);
}
