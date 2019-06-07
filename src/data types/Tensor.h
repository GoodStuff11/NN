#ifndef TENSOR_H_
#define TENSOR_H_
#include <iostream>
#include <vector>
#include <ostream>
class Tensor {
private:
	std::vector<double> data;
	std::vector<unsigned int> dim;
	unsigned int tensor_degree;
	bool reversed;
	/*
	void args_helper(std::vector<int>& v, unsigned int& index, int val) {
		if(index < v.size()) {
			v.at(index++) = val;
		}
	}
	template<typename ...Args>
	void args_helper(std::vector<int>& v, unsigned int& index, unsigned int val, Args ... args) {
		if(index < v.size()) {
			v.at(index++) = val;
			args_helper(v, index, args...);
		}
	}
	template<typename ...Args>
	std::vector<int> args2vector(Args ... args) {
		std::vector<int>indices = std::vector<int>(tensor_degree, 0);
		unsigned int values_filled = 0;
		args_helper(indices, values_filled, args...);
		return indices;
	}
	*/
	std::vector<unsigned int> reshape_matrix(bool left);
	static Tensor matrix_mul(Tensor& t1, Tensor& t2);
	// like matrix transposition except doesnt change the dimension
	void reverse() {
		reversed = !reversed;
	}
public:
	Tensor() {
		dim = {};
		tensor_degree = 0;
		reversed = 1;
		data = {};
	}
	Tensor(std::initializer_list<double> l): data(l) {
		dim = {(unsigned int)l.size()};
		tensor_degree = 1;
		reversed = 1;
	}
	unsigned int get_dim(int i) {
		return dim.at(i);
	}
	double& operator()(std::vector<unsigned int>v);
	//template<typename ...Args>
	//double& operator()(Args ... args) {
	//	return operator()(args2vector(args...));
	//}
	Tensor& operator=(Tensor const& t);
	friend Tensor operator+(Tensor t1, Tensor& t2);
	friend Tensor operator-(Tensor t1, Tensor& t2);

	friend Tensor operator-(double num, Tensor t);
	friend Tensor operator+(double num, Tensor t);
	friend Tensor operator-(Tensor t, double num);
	friend Tensor operator+(Tensor t, double num);
	friend Tensor operator*(double num, Tensor t);
	friend Tensor array2Tensor(double* array, unsigned int size);

	friend Tensor EmptyTensor(std::vector<unsigned int>dim);
	friend Tensor dot(Tensor t1, Tensor t2);
	friend Tensor tensor_product(Tensor& t1, Tensor& t2);
	friend std::ostream& operator<<(std::ostream& os, Tensor t);
	void reshape(std::vector<unsigned int> dim);

};
extern Tensor EmptyTensor(std::vector<unsigned int>dim);
extern Tensor array2Tensor(double* array, unsigned int size);
#endif
