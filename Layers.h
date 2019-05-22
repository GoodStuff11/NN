#include "data types/Matrix.h"

#include <string>
//https://www.geeksforgeeks.org/virtual-function-cpp/
class Layer {
public:
	Layer();

	Vector (*activation_function)(Vector);
	Matrix (*activation_function_derivative)(Vector);

	virtual Vector apply(Vector input) const = 0;
	virtual void update(Matrix deltaW) const = 0;
};
class dense: public Layer {
public:
	Matrix transform;
	dense(unsigned int input, unsigned int output);
	dense(unsigned int input, unsigned int output, std::string);
	virtual Vector apply(Vector input) const;
	virtual void update(Matrix deltaW) const;
};
