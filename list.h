#ifndef DATA_TYPES_LIST_H_
#define DATA_TYPES_LIST_H_

#include <iostream>
using namespace std;

template<class t>
struct element {
	t val;
	element* next;
};

template<class t>
class list {
private:
	int length;
	element<t>*first;
	element<t>*last;

	element<t>*current;
	int cindex;

	void go(int i);
public:
	list();
	~list();
	int size();
	void push_back(t val);
	t* refAt(int index);
	t valAt(int index);
	void erase(int index);

};
#include "list.cpp"

#endif
