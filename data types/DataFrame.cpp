#include "DataFrame.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
DataFrame::DataFrame() {
	return;
}
DataFrame::DataFrame(unsigned int rows, unsigned int columns) {
	this->columns = columns;
	this->rows = rows;

	data = new double*[rows];
	for (unsigned int i = 0; i < rows; i++)
		data[i] = new double[columns];

}
DataFrame::~DataFrame() {
	for (unsigned int i = 0; i < rows; i++) {
		delete data[i];
	}
	delete data;
}
double& DataFrame::operator()(unsigned int row, unsigned int column) {
	return data[row][column];
}
void DataFrame::swap(unsigned int row1, unsigned int row2) {
	double* temp = data[row1];
	data[row1] = data[row2];
	data[row2] = temp;
}

int DataFrame::Partition(int column, int left, int right) {
	double* pivot = data[right];
	int i = left;

	for (int j = left; j < right; ++j) {
		if (data[j][column] <= pivot[column]) {
			swap(i, j);
			i++;
		}
	}

	data[right] = data[i];
	data[i] = pivot;

	return i;
}

void DataFrame::QuickSortRecursive(int column, int left, int right) {
	if (left < right) {
		int q = Partition(column, left, right);
		QuickSortRecursive(column, left, q - 1);
		QuickSortRecursive(column, q + 1, right);
	}
}

void DataFrame::MaxHeapify(int column, int heapSize, int index) {
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) * 2;
	int largest = 0;

	if (left < heapSize && data[left][column] > data[index][column])
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[right][column] > data[largest][column])
		largest = right;

	if (largest != index) {
		swap(index, largest);

		MaxHeapify(column, heapSize, largest);
	}
}

void DataFrame::HeapSort(int column) {
	int heapSize = columns;

	for (int p = (heapSize - 1) / 2; p >= 0; --p) {
		MaxHeapify(column, heapSize, p);
	}

	for (int i = columns - 1; i > 0; --i) {
		swap(i, 0);

		--heapSize;
		MaxHeapify(column, heapSize, 0);
	}
}

void DataFrame::InsertionSort(int column) {
	for (unsigned int i = 1; i < columns; i++) {
		int j;

		double* key = data[i];
		j = i - 1;

		while (j >= 0 && data[j][column] > key[column]) {
			data[j + 1] = data[j];
			j = j - 1;
		}
		data[j + 1] = key;
	}
}
//intro sort
void DataFrame::sort_by(int column) {
	int partitionSize = Partition(column, 0, columns - 1);

	if (partitionSize < 16) {
		InsertionSort(column);
	} else if (partitionSize > (2 * log(columns))) {
		HeapSort(column);
	} else {
		QuickSortRecursive(column, 0, columns - 1);

	}
}
unsigned int DataFrame::get_columns() {
	return columns;
}
unsigned int DataFrame::get_rows() {
	return rows;
}
void DataFrame::read_binary_file(std::string name) {
	// make use of seekg
	std::ifstream file(name, ios::binary);
	file.read((char*) &rows, sizeof(int));
	file.read((char*) &columns, sizeof(int));
	
	data = new double*[rows];
	for (unsigned int row = 0; row < rows; row++) {
		data[row] = new double[columns];
		
		for (unsigned int column = 0; column < columns; column++) {
			file.read((char*) &data[row][column], sizeof(double));
		}
	}
	file.close();

}
void csv2binary(std::string input, std::string output) {
	ifstream inputfile(input);
	ofstream outputfile(output, ios::binary);

	string headings;
	int columns = 1;
	int rows = 1;

	// get one line and find the amount of columns in it
	outputfile.seekp(2 * sizeof(int), ios_base::beg);
	getline(inputfile, headings);
	for (unsigned int i = 0; i < headings.size(); i++)
		if (headings[i] == ',')
			columns++;

	string line;
	double value;
	// parse string already read from file
	stringstream ss(headings);
	while (getline(ss, line, ',')) {
		value = stod(line);
		outputfile.write((char*) &value, sizeof(double));
		//cout << line << ' ';
	}
	//cout << endl;

	// based on the amount of columns, parse up to
	// the ',' character and at end of line parse '\n'
	while (inputfile.good()) {
		for (int i = 0; i < columns - 1; i++) {
			getline(inputfile, line, ',');
			value = stod(line);
			outputfile.write((char*) &value, sizeof(double));
			//cout << line << " ";
		}
		getline(inputfile, line, '\n');
		//cout << line << endl;
		value = stod(line);
		outputfile.write((char*) &value, sizeof(double));
		if (inputfile.fail())
			break;
		rows++;
	}
	// write rows and columns to the start of the file
	outputfile.seekp(0, ios_base::beg);
	outputfile.write((char*) &rows, sizeof(int));
	outputfile.write((char*) &columns, sizeof(int));

	outputfile.close();
	inputfile.close();

}

ostream& operator<<(ostream& os, const DataFrame* df){
    for (unsigned int i = 0; i < df->rows; i++) {
		for (unsigned int j = 0; j < df->columns; j++) 
			cout << df->data[i][j] << ' ';
		cout << endl;
	}
    return os;
}
