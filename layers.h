#include "data types/Matrix.h"

class layer {
	void apply(Matrix *input);
	void activation(Matrix*);
	void update() {
		return;
	}
};
class dense: public layer {
	Matrix *transform;
	dense(int input, int output);
	dense(int input, int output, void activation(Matrix*));
	void apply(Matrix *input);
	void update();
};
