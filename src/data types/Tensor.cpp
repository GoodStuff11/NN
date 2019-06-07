#include "Tensor.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
Tensor EmptyTensor(std::vector<unsigned int>dim) {
	Tensor t;
	t.dim = dim;
	t.tensor_degree = dim.size();
	t.reversed = 1;

	int values = 1;
	for(unsigned int i = 0; i < t.tensor_degree; i++) {
		values *= dim.at(i);
	}
	t.data = std::vector<double>(values, 0);
	return t;
}
double& Tensor::operator()(std::vector<unsigned int>v) {
	if(v.size() != tensor_degree) {
		throw runtime_error("Tensor () operator expected " + std::to_string(tensor_degree) + " inputs. Recieved " + std::to_string(v.size()));
	}
	// {x,y,z}
	unsigned int index = 0;
	if(reversed) { // (row, column)
		// x*Y*Z + y*Z + z
		for(int i = tensor_degree - 1; i >= 0; i--) {
			int temp = v.at(i);
			if(temp != 0) {
				for(unsigned int j = i + 1; j < tensor_degree; j++) {
					temp *= dim.at(j);
				}
			}
			index += temp;
		}
	}
	else { // (x,y,z)
	   // z*Y*X + y*X + x
		for(unsigned int i = 0; i < tensor_degree; i++) {
			int temp = v.at(i);
			if(temp != 0) {
				for(int j = i - 1; j >= 0; j--) {
					temp *= dim.at(j);
				}
			}
			index += temp;
		}
	}

	return data.at(index);
}
// returns dimensions that tensor was initially
// left == 1 if it is left multiplication, otherwise 0
std::vector<unsigned int> Tensor::reshape_matrix(bool left) {
	unsigned int val = 1;
	std::vector<unsigned int> old_dim = dim;
	for(unsigned int i = 1 - left; i < tensor_degree - left; i++)
		val *= dim.at(i);

	if(left)
		dim = {val,dim.at(tensor_degree - 1)};
	else
		dim = {dim.at(0), val};

	tensor_degree = 2;
	return old_dim;
}
void Tensor::reshape(std::vector<unsigned int> dim) {
	this->dim = dim;
	tensor_degree = dim.size();
}
Tensor Tensor::matrix_mul(Tensor& t1, Tensor& t2) {
	Tensor t = EmptyTensor({t1.get_dim(0), t2.get_dim(1)});
	for(unsigned int i = 0; i < t1.dim.at(0); i++) {
		for(unsigned int j = 0; j < t2.dim.at(1); j++) {
			double sum = 0;
			for(unsigned int k = 0; k < t1.dim.at(1); k++) {
				sum += t1({i, k}) * t2({k, j});
			}
			t({i, j}) = sum;
		}
	}
	return t;
}
Tensor tensor_product(Tensor& t1, Tensor& t2) {
	std::vector<unsigned int>dim = t1.dim;
	dim.insert(dim.end(), t2.dim.begin(), t2.dim.end());

	int size1 = t1.data.size();
	int size2 = t2.data.size();
	Tensor t = EmptyTensor(dim);
	for(int i = 0; i < size1; i++)
		for(int j = 0; j < size2; j++)
			t.data.at(i * size2 + j) = t1.data.at(i) * t2.data.at(j);
	return t;
}
Tensor dot(Tensor t1, Tensor t2) {
	std::vector<unsigned int> dim1 = t1.reshape_matrix(1);
	dim1.pop_back(); //http://www.cplusplus.com/reference/vector/vector/pop_back/
	std::vector<unsigned int> dim2 = t2.reshape_matrix(0);
	dim2.erase(dim2.begin()); //https://stackoverflow.com/questions/40656871/remove-first-item-of-vector
	dim1.insert(dim1.end(), dim2.begin(), dim2.end()); //https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector

	Tensor t = Tensor::matrix_mul(t1, t2);
	t.reshape(dim1);
	return t;
}
std::ostream& operator<<(std::ostream& os, Tensor t) {
	for(unsigned int i = 0; i < t.data.size(); i++) {
		std::cout << t.data.at(i) << ' ';
		int divis = 1;
		for(unsigned int k = 0; k < t.tensor_degree; k++) {
			divis *= t.get_dim(t.tensor_degree - k - 1);
			if((i + 1) % divis == 0)
				std::cout << '\n';
		}
	}
	return os;
}
Tensor& Tensor::operator=(Tensor const& t) {
	this->data = t.data;
	this->tensor_degree = t.tensor_degree;
	this->reversed = t.reversed;
	this->dim = t.dim;
	return *this;
}
Tensor operator+(Tensor t1, Tensor& t2) {
	if(t1.dim != t2.dim) {
		throw runtime_error("Tensor dimensions are not equal");
	}
	for(int i = 0; i < t1.data.size(); i++) {
		t1.data.at(i) += t1.data.at(i);
	}
	return t1;
}
Tensor operator-(Tensor t1, Tensor& t2) {
	if(t1.dim != t2.dim) {
		throw runtime_error("Tensor dimensions are not equal");
	}
	for(int i = 0; i < t1.data.size(); i++) {
		t1.data.at(i) -= t1.data.at(i);
	}
	return t1;
}
Tensor operator*(double num, Tensor t) {
	for(int i = 0; i < t.data.size(); i++) {
		t.data.at(i) *= num;
	}
	return t;
}