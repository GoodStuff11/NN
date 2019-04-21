#include "DataFrame.h"
#include <iostream>
#include <cmath>
using namespace std;

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
void DataFrame::print() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
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

