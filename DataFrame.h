#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

class DataFrame {
private:
	int ncol;
	string *colTitle;
	vector<double*>*row;

	string* splitString(string str,char delimiter);
	double* splitNum(string str,char delimiter);
public:
	DataFrame(char* address,char delimiter);
	virtual ~DataFrame();

	void disp();
};
