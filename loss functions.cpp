#include "loss functions.h"
#include <cmath>
using namespace std;

Vector MSE(Vector input, Vector expected) {
	// sum (y-y_exp)^2
	return input - expected;
}
Vector MAE(Vector input, Vector expected) {
	// sum |y-y_exp|
	for (unsigned int i = 0; i < input.get_size(); i++) {
		if (input(i) > expected(i))
			input(i) = 1;
		else
			input(i) = -1;
	}
	return input;
}
