#include "data types/Matrix.h"

//https://www.geeksforgeeks.org/virtual-function-cpp/
class layer {
public:
	layer();
	virtual Matrix apply(Matrix input);
	Matrix (*activation)(Matrix);
	void update() {
		return;
	}
};
class dense: public layer {
public:
	Matrix transform;
	dense(unsigned int input, unsigned int output);
	dense(unsigned int input, unsigned int output, Matrix activation(Matrix));
	Matrix apply(Matrix input);
	void update();
};
