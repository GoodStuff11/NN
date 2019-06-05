#include "list.h"

template<class t>
list<t>::list() {
	length = 0;
	first = nullptr;
	last = nullptr;
	current = nullptr;
	cindex = 0;
}
template<class t>
list<t>::~list() {
	//go from one pointer to the next deleting each one
	element<t>* toDelete = first;
	for(int i = 0; i < this->size(); i++) {
		element<t>* temp = toDelete->next;
		delete toDelete;
		toDelete = temp;
	}
	delete toDelete;
	delete current;
}
template<class t>
int list<t>::size() {
	return length;
}
template<class t>
void list<t>::push_back(t val) {
	if(first == nullptr) {
		first = new element<t>{val};
		current = first;
	}
	else if(last == nullptr) {
		last = new element<t>{val};
		first->next = last;
	}
	else {
		element<t>* temp = last;
		last = new element<t>{val};
		temp->next = last;
	}
	length++;
}

template<class t>
t* list<t>::refAt(int index) {
	go(index);
	return &(current->val);
}

template<class t>
t list<t>::valAt(int index) {
	go(index);
	return current->val;
}
template<class t>
void list<t>::erase(int index) {
	element<t>* temp = first;
	for(int i = 0; i < index - 1; i++)
		temp = temp->next;

	if(index == 0) {
		first = temp->next;
		delete temp;
	}
	else if(index == this->size() - 1) {
		delete& temp->next;
		temp->next = NULL;
		last = temp;
	}
	else {
		//connect the one before to the one after
		temp->next = temp->next->next;
		delete& temp->next->next;
	}
	length--;
}
/*
 * Moves current to index i
 */
template<class t>
void list<t>::go(int i) {
	if(i < cindex) {
		current = first;
		cindex = 0;
	}
	for(; cindex < i; cindex++) {
		current = current->next;
	}
}
