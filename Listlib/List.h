#ifndef _LIST_
#define _LIST_
#include <iostream>

using namespace std;

template <class ValType>
class ListElem {
protected:
	ValType list;
	ListElem* next;
	ListElem* previous;
public:
	ListElem(ValType list);
	~ListElem();

	ValType GetList();
	ListElem* GetNext();
	ListElem* GetPrevious();

	void SetList(ValType list);
	void SetNext(ListElem* next);
	void SetPrevious(ListElem* previous);

	template <class ValType1>
	friend ostream& operator<<(ostream& ostr, const ListElem<ValType1>& v);
	template <class ValType1>
	friend istream& operator>>(istream& istr, ListElem<ValType1>& v);
};

template<class ValType>
inline ListElem<ValType>::ListElem(ValType list) {
	this->list = list;
	next = 0;
	previous = 0;
}

template<class ValType>
inline ListElem<ValType>::~ListElem() {
	next = 0;
	previous = 0;
}

template<class ValType>
inline ValType ListElem<ValType>::GetList() {
	return list;
}

template<class ValType>
inline ListElem<ValType>* ListElem<ValType>::GetNext() {
	return next;
}

template<class ValType>
inline ListElem<ValType>* ListElem<ValType>::GetPrevious(){
	return previous;
}

template<class ValType>
inline void ListElem<ValType>::SetList(ValType list) {
	this->list = list;
}

template<class ValType>
inline void ListElem<ValType>::SetNext(ListElem<ValType>* next) {
	this->next = next;
}

template<class ValType>
inline void ListElem<ValType>::SetPrevious(ListElem* previous){
	this->previous = previous;
}

template<class ValType1>
inline ostream& operator<<(ostream& ostr, const ListElem<ValType1>& v) {
	ostr << v.list;
	return ostr;
}

template<class ValType1>
inline istream& operator>>(istream& istr, ListElem<ValType1>& v) {
	istr >> v.list;
	return istr;
}



template<class ValType>
class TList {
protected:
	ListElem<ValType>* first;
	ListElem<ValType>* last;
	int length;
public:
	TList();
	TList(TList<ValType>& v);
	~TList();

	TList<ValType>& operator= (TList<ValType>& v);

	void InsFirst(ValType temp);
	void InsLast(ValType temp);
	void InsAfter(ListElem<ValType>* element, ValType temp);

	void DelFirst();
	void DelLast();
	void DelAfter(ListElem<ValType>* element);

	ListElem<ValType>* GetFirst();
	ListElem<ValType>* GetLast();

	bool IsEmpty(void) const;
	bool IsFull(void) const;

	template <class ValType1>
	friend ostream& operator<<(ostream& ostr, const TList<ValType1>& v);
	template <class ValType1>
	friend istream& operator>>(istream& istr, TList<ValType1>& v);
};


template <class ValType>
TList<ValType>::TList() {
	length = 0;
	first = 0;
	last = 0;
}

template <class ValType>
TList<ValType>::TList(TList<ValType>& v) {
	this->length = v.length;
	ListElem<ValType>* list1 = this->first;
	ListElem<ValType>* list2 = v.first;
	ListElem<ValType>* list3 = 0;
	while (list2 != 0) {
		list1 = new ListElem<ValType>(*list2);
		list1->SetNext(0);
		if (list3 != 0) {
			list3->SetNext(list1);
			list1->SetPrevious(list3);
		}
		list3 = list1;
		if (first == 0) first = list1;
		last = list1;
		list2 = list2->GetNext();
	}
}

template <class ValType>
TList<ValType>::~TList() {
	if(this->first != 0) {
		ListElem<ValType>* list1 = this->first;
		ListElem<ValType>* list3 = 0;
		while (list1 != 0) {
			list3 = list1;
			list1 = list1->GetNext();
			delete list3;
		}
		this->first = 0;
		this->last = 0;
		length = 0;
	}
}

template <class ValType>
TList<ValType>& TList<ValType>:: operator= (TList<ValType>& v)
{
	if (this == &v)
		return (*this);
	if (this->first != 0) {
		ListElem<ValType>* list1 = this->first;
		ListElem<ValType>* list3 = 0;
		while (list1 != 0) {
			list3 = list1;
			list1 = list1->GetNext();
			delete list3;
		}
		this->first = 0;
		this->last = 0;
		length = 0;
	}
	this->length = v.length;
	ListElem<ValType>* list1 = this->first;
	ListElem<ValType>* list2 = v.first;
	ListElem<ValType>* list3 = 0;
	while (list2 != 0) {
		list1 = new ListElem<ValType>(*list2);
		list1->SetNext(0);
		if (list3 != 0) {
			list3->SetNext(list1);
			list1->SetPrevious(list3);
		}
		list3 = list1;
		if (this->first == 0) this->first = list1;
		last = list1;
		list2 = list2->GetNext();
	}
}

template <class ValType>
void TList<ValType>::InsFirst(ValType temp) {
	ListElem<ValType>* tmp = new ListElem<ValType>(temp);
	tmp->SetNext(first);
	first = tmp;
	length++;
}

template <class ValType>
void TList<ValType>::DelFirst() {
	if (first == 0)
		throw logic_error("Input error: invalide value of List length in DelFirst");
	ListElem<ValType>* list1 = first;
	first = first->GetNext();
	delete list1;
	length--;
}

template <class ValType>
void TList<ValType>::DelLast() {
	if (this->IsEmpty())
		throw logic_error("Input error: invalide value of List length in DelLast");
	ListElem<ValType>* list2 = last;
	last = last->GetPrevious();
	delete list2;
	length--;
}

template<class ValType>
void TList<ValType>::DelAfter(ListElem<ValType>* element){
	element->GetPrevious()->SetNext(element->GetNext());
	element->GetNext()->SetPrevious(element->GetPrevious());
	delete element;
	length--;
}

template <class ValType>
void TList<ValType>::InsLast(ValType temp) {
	ListElem<ValType>* tmp = new ListElem<ValType>(temp);
	tmp->SetPrevious(last);
	last = tmp;
	length++;
}

template<class ValType>
inline void TList<ValType>::InsAfter(ListElem<ValType>* element, ValType temp){
	ListElem<ValType>* tmp = new ListElem<ValType>(temp);
	tmp->SetNext(element->GetNext());
	tmp->SetPrevious(element);
	element->GetNext()->SetPrevious(tmp);
	element->SetNext(tmp);
	length++;
}

template<class ValType>
ListElem<ValType>* TList<ValType>::GetFirst(){
	return first;
}

template<class ValType>
ListElem<ValType>* TList<ValType>::GetLast(){
	return last;
}

template <class ValType>
bool TList<ValType>::IsEmpty(void) const {
	return length == 0;
}

template <class ValType>
bool TList<ValType>::IsFull(void) const {
	try {
		ListElem<ValType>* tmp = new ListElem<ValType>(0);
		tmp->SetPrevious(last);
		delete tmp;
		return false;
	}
	catch ("List Isfull"){
		return true;
	}
}

template<class ValType1>
ostream& operator<<(ostream& ostr, const TList<ValType1>& v) {
	ListElem<ValType1>* tmp = v.first;
	while (tmp != 0) {
		ostr << *tmp << endl;
		tmp = tmp->GetNext();
	}
	return ostr;
}

template<class ValType1>
istream& operator>>(istream& istr, TList<ValType1>& v) {
	int count;
	istr >> count;
	for (int i = 0; i < count; i++) {
		ValType1 time;
		istr >> time;
		v.InsLast(time);
	}
	return istr;
}




#endif