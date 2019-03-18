#include "DataFrame.h"
#include "list.h"

DataFrame::DataFrame(const char *address, char delimiter) {
	row = new list<double*>();

	ifstream datafile(address);
	string line;

	if (datafile.is_open()) {
		getline(datafile, line);
		//https://stackoverflow.com/questions/3867890/count-character-occurrences-in-a-string
		ncol = count(line.begin(), line.end(), delimiter) + 1;
		colTitle = splitString(line, delimiter);

		while (getline(datafile, line)) {
			row->push_back(splitNum(line, delimiter));
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

		result[i] = stod(substr.c_str());
		//result[i] = strtod(substr.c_str(),NULL);
		i++;
	}

	return result;
}
void DataFrame::sort(int col) {
	quicksort(row,0,row->size()-1,col);
}
//ripped straight off Lomuto partition scheme https://en.wikipedia.org/wiki/Quicksort
void DataFrame::quicksort(list<double*>*L,int lo,int hi,int col){
	if (lo < hi){
		int p = partition(L,lo,hi,col);
		quicksort(L,lo,p-1,col);
		quicksort(L, p+1,hi,col);
	}
}
int DataFrame::partition(list<double*>*L,int lo,int hi,int col){
	double* pivot = L->valAt(hi);
	int i = lo;
	for (int j = lo; j<hi -1;j++){
		if (L->valAt(j)[col] < pivot[col]){
			L->swap(i,j);
			i++;
		}
	}
	L->swap(i,hi);
	return i;
}

void DataFrame::disp() {
	//cout << "Columns: " << ncol << endl;
	//cout << "Rows: " << row->size() << endl;

	for (int i = 0; i < ncol; i++) {
		cout << colTitle[i] << '\t';
	}
	cout << endl;
	for (int i = 0; i < row->size(); i++) {
		for (int j = 0; j < ncol; j++) {
			cout << row->valAt(i)[j] << '\t';
		}
		cout << endl;
	}
}

