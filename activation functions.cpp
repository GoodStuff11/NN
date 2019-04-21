#include "activation functions.h"

void softmax(Matrix *mat){
	double sum = 0;
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->columns;j++)
			sum += (*mat)(i,j);
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->columns;j++)
			(*mat)(i,j) /= sum;
}
void sigmoid(Matrix *mat){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++)
			(*mat)(i,j) = 1/(exp(-(*mat)(i,j)) + 1);
}
void softplus(Matrix *mat){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++)
			(*mat)(i,j) = log(1+exp((*mat)(i,j)));
}
void tanh(Matrix *mat){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++)
			(*mat)(i,j) = tanh((*mat)(i,j));
}
void relu(Matrix *mat){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++){
			double val = (*mat)(i,j);
			if (val<0)
				(*mat)(i,j) = 0;
			else
				(*mat)(i,j) = val;
		}
}
void elu(Matrix *mat,double a){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++){
			double val = (*mat)(i,j);
			if (val<0)
				(*mat)(i,j) = a*(exp(val) - 1);
			else
				(*mat)(i,j) = val;
		}
}
void leaky_relu(Matrix *mat,double a){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++){
			double val = (*mat)(i,j);
			if (val<0)
				(*mat)(i,j) = a*val;
			else
				(*mat)(i,j) = val;
		}
}
void step(Matrix *mat){
	for (unsigned int i=0;i<mat->rows;i++)
		for (unsigned int j=0;j<mat->rows;j++){
			if ((*mat)(i,j)<0)
				(*mat)(i,j) = 0;
			else
				(*mat)(i,j) = 1;
		}
}
void none(Matrix *mat){
	return;
}
