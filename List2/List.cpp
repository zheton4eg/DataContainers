#include "List.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////                 ConstIterators                //////////////////////////////

//ConstIterator

template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor\t" << this << endl;
#endif // DEBUG
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

//ConstReverseIterator
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RitConstructor:\t" << this << endl;
#endif DEBUG
}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RitDestructor:\t" << this << endl;
#endif DEBUG
}
//     Incremento/Decremento:
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//ConstBaseIterators:

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
//      Dereference operators:
template<typename T>T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}



////////////////////////////                 ConstIterators                //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////                 Iterators                //////////////////////////////

template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

////////////////////////////                 Iterators                //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


///----------------------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////               List members               //////////////////////////////  


template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

template <typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif DEBUG
}

template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}

template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
#ifdef DEBUG
	cout << "CopyConstructor:" << this << endl;
#endif DEBUG
}

template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	//while (Head)pop_front();
#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif DEBUG
}


//	Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return*this;
	{
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif DEBUG
		return *this;
	}

}


//            Adding elements:
template <typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
	}
	size++;
}
//          Removing elements: 
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else {
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}
template<typename T>void List<T>::insert(T Data, int index)
{
	Element* New = new Element(Data);
	if (index == 0)return push_front(Data);
	if (size <= index)return push_back(Data);
	if (index < size / 2)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev = New;
		Temp->pPrev->pPrev->pNext = New;
	}
	else
	{
		Element* Temp = Tail;
		for (int i = 0; i < (size - index) - 1; i++)Temp = Temp->pPrev;
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev = New;
		Temp->pPrev->pPrev->pNext = New;
	}
	size++;
}

template<typename T>void List<T>::erase(int index)
{
	if (index == 0)return pop_front();
	if (index > size)return pop_back();
	if (index < size / 2)
	{
		Element* Temp = Head;

		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		Element* erased = Temp;
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete erased;
	}
	else
	{
		Element* Temp = Tail;

		for (int i = 0; i < (size - index) - 1; i++)Temp = Temp->pPrev;
		Element* erased = Temp;
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete erased;
	}
	size--;
}
//         Methods:
template<typename T>void List<T>::print()const
{
	cout << delimiter << endl;
	cout << "Head: \t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab
		<< Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Кол-во элементов списка: " << size << endl;
	cout << delimiter << endl;
}

template<typename T>void List<T>::reverse_print()const
{
	cout << delimiter << endl;
	cout << "Tail: \t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)

		cout << Temp->pPrev << tab << Temp << tab
		<< Temp->Data << tab << Temp->pNext << endl;
	cout << "Head:\t" << Head << endl;
	cout << "Кол-во элементов списка: " << size << endl;
	cout << delimiter << endl;
}
////////////////////////////               List members               //////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////////////////////// 

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{

	for (typename List<T> ::Iterator it = list.begin(); it != list.end(); ++it)
	{
		*it *= 10;
	}

}