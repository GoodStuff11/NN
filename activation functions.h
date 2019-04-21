#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_
#include "Matrix.h"
#include <cmath>

void softmax(Matrix *mat);
void sigmoid(Matrix *mat);
void relu(Matrix *mat);
void leaky_relu(Matrix *mat,double a);
void tanh(Matrix *mat);
void elu(Matrix *mat,double a);
void step(Matrix *mat);
void softplus(Matrix *mat);
void none(Matrix *mat);

#endif /* ACTIVATION_FUNCTIONS_H_ */
