#include "data types/Matrix.h"

#include <string>
//https://www.geeksforgeeks.org/virtual-function-cpp/
class Layer {
	unsigned int nodes;
public:
	unsigned int getNodes() const;
protected:
	Vector (*activation_function)(Vector);
	Matrix (*activation_function_derivative)(Vector);
	void decodeActivationFunction(std::string function);
	
	virtual Vector call(Vector input) const = 0;
	
	virtual Matrix calculate_s(Vector error, Vector nodes) const = 0;
	virtual Matrix update(Vector s, Vector nodes) = 0;
	virtual void build(Layer *previous_layer) = 0;
};
class dense: public Layer {
	Matrix weights;
public:
	dense(unsigned int output);
	dense(unsigned int output, std::string function);
	virtual Vector call(Vector input) const;
	
	virtual Matrix calculate_s(Vector error, Vector nodes) const;
	virtual Matrix update(Vector s, Vector nodes);
	virtual void build(Layer *previous_layer);
};
class activation: public Layer {
public:
	activation(std::string function);
	virtual Vector call(Vector input) const;
	
	virtual Matrix calculate_s(Vector error, Vector nodes) const;
	virtual Matrix update(Vector s, Vector nodes);
	virtual void build(Layer *previous_layer);
};
