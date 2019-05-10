#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

#include "data types/Matrix.h"
#include <string>
class activation {
private:
	string function;
	double constant;
public:
	activation(string function);
	activation(string function,double constant);
			
	Matrix call_derivative(Vector input);
	Vector call(Vector input);
};

#endif /* ACTIVATION_FUNCTIONS_H_ */
