#ifndef DATAFRAME_H_
#define DATAFRAME_H_

class DataFrame {
private:
	double** data;

	int Partition(int column, int left, int right);
	void QuickSortRecursive(int column, int left, int right);
	void MaxHeapify(int column, int heapSize, int index);
	void HeapSort(int column);
	void InsertionSort(int column);

public:
	unsigned int columns;
	unsigned int rows;
	void sort_by(int column);
	DataFrame(unsigned int rows, unsigned int columns);
	virtual ~DataFrame();
	double &operator()(unsigned int row, unsigned int column);
	void print();
	void swap(unsigned int row1, unsigned int row2);

};

#endif /* DATAFRAME_H_ */
