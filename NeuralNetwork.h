#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
#include "data types/list.h"
#include "layers.h"
#include "activation functions.h" //so that main doesn't have to include this
#include "data types/DataFrame.h"

class NeuralNetwork {
private:
	list<layer*> *model;
	Vector (*loss_function)(Vector, Vector);
public:
	void set_loss_function(std::string function);
	Vector predict(Vector input);
	NeuralNetwork();
	virtual ~NeuralNetwork();
	void add_layer(layer *new_layer);
	void fit(DataFrame train_data, DataFrame train_labels);
};

#endif /* NEURALNETWORK_H_ */
