#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

#include "data types/Matrix.h"
#include <string>

namespace af{
Vector softmax(Vector v);
Vector sigmoid(Vector v);
Vector softplus(Vector v);
Vector tanh(Vector v);
Vector relu(Vector v);
Vector elu(Vector v);
Vector leaky_relu(Vector v);
Vector step(Vector v);
Vector none(Vector v);

Matrix softmax_derivative(Vector v);
Matrix relu_derivative(Vector v);
Matrix sigmoid_derivative(Vector v);
Matrix none_derivative(Vector v);
}

#endif /* ACTIVATION_FUNCTIONS_H_ */
