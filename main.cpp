#include "DataFrame.h"

using namespace std;

int main() {
	char* address = "S:/data/data1.txt";
	DataFrame *df = new DataFrame(address,',');
	df->disp();
}
