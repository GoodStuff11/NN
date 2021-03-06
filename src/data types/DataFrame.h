#ifndef DATAFRAME_H_
#define DATAFRAME_H_
#include <string>
#include <iostream>
class DataFrame {
private:
	unsigned int columns;
	unsigned int rows;

	double** data;

	int Partition(int column, int left, int right);
	void QuickSortRecursive(int column, int left, int right);
	void MaxHeapify(int column, int heapSize, int index);
	void HeapSort(int column);
	void InsertionSort(int column);

public:
	DataFrame();
	DataFrame(unsigned int rows, unsigned int columns);
	virtual ~DataFrame();

	unsigned int get_columns();
	unsigned int get_rows();

	void sort_by(int column);
	double& operator()(unsigned int row, unsigned int column);
	double* operator[](unsigned int row);
	DataFrame* operator=(DataFrame* df);
	void swap(unsigned int row1, unsigned int row2);
	void read_binary_file(std::string name);
	friend std::ostream& operator<<(std::ostream& os, const DataFrame* df);
};
void csv2binary(std::string input, std::string output);
void csv2binary(std::string input);
DataFrame* read_binary_file(std::string name);
#endif /* DATAFRAME_H_ */
