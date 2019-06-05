#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
#include "data types/list.h"
#include "activation functions.h" //so that main doesn't have to include this
#include "data types/DataFrame.h"
#include "Layer.h"

class NeuralNetwork {
private:
	list<Layer*>* model;
	Vector(*loss_function)(Vector, Vector);
	Vector* calculate_nodes(Vector input);
public:
	void set_loss_function(std::string function);
	Vector predict(Vector input);
	NeuralNetwork();
	virtual ~NeuralNetwork();
	void add_layer(Layer* new_layer);
	void build(std::string function);
	void fit(DataFrame& train_data, DataFrame& train_labels, unsigned int epochs);
};

#endif /* NEURALNETWORK_H_ */
