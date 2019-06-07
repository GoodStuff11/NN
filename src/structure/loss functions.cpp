#include "loss functions.h"
#include <cmath>
#include <iostream>
using namespace std;

Tensor MSE(Tensor input, Tensor expected) {
	// sum (y-y_exp)^2
	return input - expected;
}
Tensor MAE(Tensor input, Tensor expected) {
	// sum |y-y_exp|
	for(unsigned int i = 0; i < input.get_dim(0); i++) {
		if(input({i}) > expected({i}))
			input({i}) = 1;
		else
			input({i}) = -1;
	}
	return input;
}
