#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n-----------------------------------------------------------------\n"
#include<string>

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor: \t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: \t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		//      Dereference operators:
		T operator*()const
		{
			return Temp->Data;
		}

	};
public:

	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "ItConstructor\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor\t" << this << endl;
		}
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RitConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RitDestructor:\t" << this << endl;
		}
		//     Incremento/Decremento:
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator& operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator& operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}

	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//	Operators:
	List<T>& operator=(const List<T>& other);

	//            Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	//          Removing elements: 
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	void erase(int index);
	//         Methods:
	void print()const;
	void reverse_print()const;
};

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
	cout << "LConstructor:\t" << this << endl;
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
	cout << "CopyConstructor:" << this << endl;
}

template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	//while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}


//	Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return*this;
	{
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
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

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите кол-во элементов списка: "; cin >> n;
	List glist;
	for (int i = 0; i < n; i++)
	{
		glist.push_front(rand() % 100);
		//glist.push_back(rand() % 100);
	}
	glist.print();
	//glist.reverse_print();
	/*for (int i = 0; i < 100; i++)glist.pop_back();
	glist.reverse_print();*/
	int index, Data;
	cout << "Введите индек элемента: "; cin >> index;
	cout << "Введите элемент: "; cin >> Data;

	glist.insert(Data, index);
	glist.print();
	glist.erase(index);
	glist.print();
#endif // BASE_CHECK

	//List list = { 3,5,8,13,21 };
	//List list2 = {34,55,89,144,233 };
	//list2.print();

	//for (int i : list)cout << i << tab; cout << endl;
	//List list = { 3,5,8,13,21 };
	//for(List::ReverseIterator it = list.rbegin(); it != list.rend(); it++)
	//{
	//	//cout << *it << tab;
	//}
	//cout << endl;

	List<int> list = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list + list2;
	/*list3.print();
	list3.reverse_print();*/
	for (int i : list)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;


	List<double> d_list = { 2.7,3.14,5.4,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "хорошо" ,"живёт" };
	for (std::string i : s_list)cout << i << tab;
	cout << endl;

}