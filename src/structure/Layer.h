#include "../data types/Tensor.h"
#include <iostream>
#include <string>

class Layer {
public:
	virtual std::string name() { return "Layer"; }
	unsigned int getNodes() const;
	friend class NeuralNetwork; // allow access to build()
	virtual void set_activation_function(std::string str) { decodeActivationFunction(str); }
protected:
	double training_rate;
	unsigned int nodes;
	Tensor(*activation_function)(Tensor);
	Tensor(*activation_function_derivative)(Tensor);
	void decodeActivationFunction(std::string function);

	virtual Tensor call(Tensor input) { return Tensor(); };

	Tensor calculate_s(Tensor error, Tensor nodes) const;
	virtual Tensor update(Tensor s, Tensor nodes) { return Tensor(); }
	virtual void build(Layer* previous_layer) {}
	
	virtual void print() {};
};
class dense: public Layer {
	Tensor weights;
	Tensor biases;
	
public:
	std::string name() { return "dense"; }
	dense(unsigned int output);
	dense(unsigned int output, std::string function);
	Tensor call(Tensor input);

	Tensor update(Tensor s, Tensor nodes);
	void build(Layer* previous_layer);
	virtual void print() { std::cout << weights << std::endl; }
	virtual void set_activation_function(std::string str) { decodeActivationFunction(str); }
};
class input: public Layer {
public:
	input(unsigned int input) {
		nodes = input;
	}
	std::string name() { return "input"; }
	Tensor call(Tensor input) { return Tensor(); }
	Tensor update(Tensor s, Tensor nodes) { return Tensor(); }
	void build(Layer* previous_layer) {}
	virtual void print() {};
	virtual void set_activation_function(std::string str) { }
};
class activation: public Layer {
public:
	activation(std::string function);
	std::string name() { return "activation"; }
	Tensor call(Tensor input);

	Tensor update(Tensor s, Tensor nodes) { return s; }
	void build(Layer* previous_layer) {}
	virtual void print() {};
	virtual void set_activation_function(std::string str) { decodeActivationFunction(str); }
};
