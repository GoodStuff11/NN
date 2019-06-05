#include "data types/Matrix.h"
#include <iostream>
#include <string>
//https://www.geeksforgeeks.org/virtual-function-cpp/
class Layer {
public:
	virtual std::string name() { return "Layer"; }
	unsigned int getNodes() const;
	friend class NeuralNetwork; // allow access to build()
protected:
	unsigned int nodes;
	Vector(*activation_function)(Vector);
	Matrix(*activation_function_derivative)(Vector);
	void decodeActivationFunction(std::string function);

	virtual Vector call(Vector input) { return 0; };

	Vector calculate_s(Vector error, Vector nodes) const;
	virtual Vector update(Vector s, Vector nodes) { return 0; }
	virtual void build(Layer* previous_layer) {}
};
class dense: public Layer {
	Matrix weights;
	Vector biases;
public:
	std::string name() { return "dense"; }
	dense(unsigned int output);
	dense(unsigned int output, std::string function);
	Vector call(Vector input);

	Vector update(Vector s, Vector nodes);
	void build(Layer* previous_layer);
};
class input: public Layer {
public:
	input(unsigned int input) {
		nodes = input;
	}
	std::string name() { return "input"; }
	Vector call(Vector input) { return 0; }
	Vector update(Vector s, Vector nodes) { return 0; }
	void build(Layer* previous_layer) {}

};
class activation: public Layer {
public:
	activation(std::string function);
	std::string name() { return "activation"; }
	Vector call(Vector input);

	Vector update(Vector s, Vector nodes) { return s; }
	void build(Layer* previous_layer) {}
};
