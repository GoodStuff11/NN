#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include "list.h"

using namespace std;

class DataFrame {
private:
	int ncol = 0;
	string *colTitle;
	list<double*>*row;

	string* splitString(string str, char delimiter);
	double* splitNum(string str, char delimiter);

	int partition(list<double*>*L,int lo,int hi,int col);
	void quicksort(list<double*>*L,int lo,int hi,int col);
public:
	DataFrame(const char* address, char delimiter);
	virtual ~DataFrame();
	void disp();
	void sort(int col);

};
