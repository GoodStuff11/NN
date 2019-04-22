#include "activation functions.h"

Matrix softmax::call(Matrix mat){
	double sum = 0;
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.columns;j++)
			sum += exp(mat(i,j));
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.columns;j++)
			mat(i,j) = exp(mat(i,j))*sum;
	return mat;
}
Matrix softmax::call_derivative(Matrix mat){
	double sum = 0;
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.columns;j++)
			sum += exp(mat(i,j));
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.columns;j++)
			mat(i,j) = exp(mat(i,j))*sum;
	return mat;
}
Matrix sigmoid::call(Matrix mat){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++)
			mat(i,j) = 1/(exp(-mat(i,j)) + 1);
	return mat;
}
Matrix softplus::call(Matrix mat){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++)
			mat(i,j) = log(1+exp(mat(i,j)));
	return mat;
}
Matrix tanh::call(Matrix mat){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++)
			mat(i,j) = tanh(mat(i,j));
	return mat;
}
Matrix relu::call(Matrix mat){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++){
			double val = mat(i,j);
			if (val<0)
				mat(i,j) = 0;
			else
				mat(i,j) = val;
		}
	return mat;
}
Matrix elu::call(Matrix mat,double a){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++){
			double val = mat(i,j);
			if (val<0)
				mat(i,j) = a*(exp(val) - 1);
			else
				mat(i,j) = val;
		}
	return mat;
}
Matrix leaky_relu::call(Matrix mat,double a){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++){
			double val = mat(i,j);
			if (val<0)
				mat(i,j) = a*val;
			else
				mat(i,j) = val;
		}
	return mat;
}
Matrix step::call(Matrix mat){
	for (unsigned int i=0;i<mat.rows;i++)
		for (unsigned int j=0;j<mat.rows;j++){
			if (mat(i,j)<0)
				mat(i,j) = 0;
			else
				mat(i,j) = 1;
		}
	return mat;
}
Matrix none::call(Matrix mat){
	return mat;
}
