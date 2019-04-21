#ifndef LOSS_FUNCTIONS_H_
#define LOSS_FUNCTIONS_H_
#include "Matrix.h"

double MSE(Matrix *input, Matrix *expected);
double MAE(Matrix *input, Matrix *expected);

#endif /* LOSS_FUNCTIONS_H_ */
