#include "data types/Matrix.h"

#include <string>
//https://www.geeksforgeeks.org/virtual-function-cpp/
class layer {
public:
	layer();
	virtual Vector apply(Vector input);
	Vector (*activation_function)(Vector);
	Matrix (*activation_function_derivative)(Vector);
	virtual void update(Matrix deltaW) = 0;
};
class dense: public layer {
public:
	Matrix transform;
	dense(unsigned int input, unsigned int output);
	dense(unsigned int input, unsigned int output, std::string);
	Vector apply(Vector input);
	void update(Matrix deltaW);
};
