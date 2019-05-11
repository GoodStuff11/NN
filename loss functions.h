#ifndef LOSS_FUNCTIONS_H_
#define LOSS_FUNCTIONS_H_
#include "data types/Matrix.h"
#include <string>

Vector MSE(Vector input, Vector expected);
Vector MAE(Vector input, Vector expected);

#endif /* LOSS_FUNCTIONS_H_ */
