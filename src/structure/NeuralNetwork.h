#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_
#include "../data types/list.h"
#include "activation functions.h" //so that main doesn't have to include this
#include "../data types/DataFrame.h"
#include "../data types/Tensor.h"
#include "Layer.h"

class NeuralNetwork {
private:
	double training_rate;
	Tensor(*loss_function)(Tensor, Tensor);
	Tensor* calculate_nodes(Tensor input);
	void set_loss_function(std::string function);
public:
	friend class Layer;
	list<Layer*>* layers;
	void set_training_rate(double rate);
	Tensor predict(Tensor input);
	NeuralNetwork();
	NeuralNetwork(double training_rate);
	virtual ~NeuralNetwork();
	void add_layer(Layer* new_layer);
	void build(std::string function);
	void fit(DataFrame& train_data, DataFrame& train_labels, unsigned int epochs);
};

#endif /* NEURALNETWORK_H_ */
