#include "DataFrame.h"
#include <cstdlib>
DataFrame::DataFrame(char* address, char delimiter) {
	ifstream datafile(address);
	string line;

	if (datafile.is_open()) {
		getline(datafile, line);
		//https://stackoverflow.com/questions/3867890/count-character-occurrences-in-a-string
		ncol = count(line.begin(), line.end(), delimiter) + 1;
		colTitle = splitString(line,delimiter);

		while (getline(datafile, line)) {
			double *x = splitNum(line,delimiter);
			cout<<"hey";
			row->push_back(x);
		}
		datafile.close();
	}

}

DataFrame::~DataFrame() {
	cout << "YOU CAN'T SILENCE ME!!!" << endl;
	delete row;
	delete colTitle;
}
//https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
string* DataFrame::splitString(string str, char delimiter) {
	cout << "split string" << endl;
	stringstream ss(str);
	string* result = new string[ncol];

	int i = 0;
	while (ss.good()) {
		string substr;
		getline(ss, substr, delimiter);
		result[i] = substr;
		i++;
	}
	return result;
}
double* DataFrame::splitNum(string str, char delimiter) {
	stringstream ss(str);
	double* result = new double[ncol];
	int i = 0;
	while (ss.good()) {
		string substr;

		getline(ss, substr, delimiter);

		//result[i] = stod(substr.c_str());
		result[i] = strtod(substr.c_str(),NULL);
		i++;
	}
	return result;
}
void DataFrame::disp(){
	for (int i = 0; i<ncol;i++){
		cout << colTitle[i] << endl;
	}
}

