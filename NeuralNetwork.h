#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
#include "data types/list.h"
#include "layers.h"
#include "activation functions.h" //so that main doesn't have to include this

class NeuralNetwork {
private:
	list<layer*> *model;
	double loss_function(Matrix*, Matrix*);
public:
	void set_loss_function(double loss_function(Matrix*, Matrix*));
	NeuralNetwork();
	virtual ~NeuralNetwork();
	void add_layer(layer *new_layer);
};

#endif /* NEURALNETWORK_H_ */
