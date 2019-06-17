#pragma once
#include "Iterator.h"
#include "Bus.h"
#include <iostream>
using namespace std;
template <class T>
class List {
	struct ListNode {
		T data;
		ListNode * next;Ö
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
			next = NULL;
		}
		void Print(){
			cout << data;
		}
	};
public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	List();
	~List(){
		clear();
	}
	iterator begin() {
		if (this->first == NULL){
			return NULL;
		}
		else{
			return *this->first;
		}
	} 
	iterator end(){
		if (this->last == NULL)
		{
			return NULL;
		}
		else
		{
			return *this->last;
		}
	}
	void clear();
	bool empty();
	iterator find(const node_type & val)
	{
		node_type *tmp = head;
		while (tmp!=NULL)
		{
			if (tmp->data == val.data)
			{
				return iterator(tmp);
			}
			tmp = tmp->next;
		}
		return NULL;
	}
	void pop_front();

	void push_front(const node_type val);
	void remove(const node_type val);


	int size();

	void splice(iterator _Where, List<T>& _Right);
	void Print();
private:
	node_type *head;
	iterator *first, *last;
};

template<class T>
List<T>::List(){
	this->head = NULL;
	this->first = NULL;
	this->last = NULL;
}

template<class T>
inline int List<T>::size(){
	node_type *tmp = head;
	int count = 0;
	while (tmp != NULL){
		count++;
		tmp = tmp->next;
	}
	return count;
}

template<class T>
inline void List<T>::splice(iterator _Where, List<T>& _Right){
	if (_Where != NULL) {
		iterator i = this->begin();
		iterator prev;
		node_type *tmp = head;
		while (tmp != NULL){
			if (tmp->data == (*_Where).data){
				_Right.push_front(*i);
				if (tmp == head)
					this->pop_front();
				else{
					(*prev).next = (*i).next;
					delete &(*(i));
				}
				break;
			}
			prev = i;
			i++;
			tmp = tmp->next;
		}
	}
}

template<class T>
inline void List<T>::Print(){
	node_type* tmp = head;
	while (tmp != NULL){
		tmp->Print();
		tmp = tmp->next;
	}
}

template<class T>
inline void List<T>::clear(){
	node_type *tmp;
	while (head!=NULL){
		tmp = head;
		head = head->next;
		delete tmp;
	}
	first = NULL;
	last = NULL;
}

template<class T>
inline bool List<T>::empty(){	
	if (this->size() == 0){
		return true;
	}
	else{
		return false;
	}
}

template<class T>
inline void List<T>::pop_front(){
	if (head != NULL){
		node_type *tmp;
		tmp = head;
		head = head->next;
		delete tmp;
		first = new iterator(head);
		if (head == NULL){
			last = new iterator(head);
		}
	}
}

template<class T>
inline void List<T>::push_front(const node_type val){
	node_type *tmp = new ListNode();
	*tmp = val;
	tmp->next = head;
	head = tmp;
	if (last == NULL){
		last = new iterator(head);
	}
	first = new iterator(head);
}

template<class T>
inline void List<T>::remove(const node_type val){
	node_type *curent = head;
	node_type *prev = NULL;
	while (curent != NULL){
		if (curent->data == val.data){
			node_type *for_del= curent;
			if (prev == NULL){
				head = curent->next;
				*first = iterator(head);
			}
			else{
				prev->next = curent->next;
				if (curent->next == NULL)
					*last = iterator(curent);
			}
			delete for_del;
			return;
		}
		prev = curent;
		curent = curent->next;
	}
}
