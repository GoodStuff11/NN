#ifndef LOSS_FUNCTIONS_H_
#define LOSS_FUNCTIONS_H_
#include "../data types/Tensor.h"
#include <string>

Tensor MSE(Tensor input, Tensor expected);
Tensor MAE(Tensor input, Tensor expected);

#endif /* LOSS_FUNCTIONS_H_ */
