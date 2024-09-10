#include<iostream>
using namespace std;
#define tab "\t"

//#define BASE_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FROM_ARRAY

class Element
{
	protected:
	int Data;        
	Element* pNext;
	unsigned static int count;

public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor\t\t\t" << this << endl;	
	}
	~Element()
	{
		count--;
		cout << "EDestructor\t\t\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
	friend class Stack;
};

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor: \t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}

};

unsigned int Element::count = 0;
class ForwardList
{
protected:
	Element* Head;
	unsigned int size;
public: 

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ForwardList()
	{
		size = 0;
		Head = nullptr;
		cout << "LConstructor:\t\t\t" << this << endl;
	}

	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		
		cout << "LDestructor:\t" << this << endl;
	}
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		if (other.size == 0)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}
	//         Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);

		size++;
    }
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
	/*	Element* New = new Element(Data);

		Temp->pNext = New;*/
		Temp->pNext = new Element(Data);
		size++;
	}
	/*void pop_front()
	{
		Element* Temp = Head;
		
		Head = Temp->pNext;
	}*/
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	/*void pop_back(int& n)
	{
		Element* Temp = Head;
		
		for(int i=0;i<n-1;i++ )
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = nullptr;
	}*/
	void pop_back()
	{
		if (Head == nullptr|| Head->pNext == nullptr)return pop_front();
		
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	//void insert(int Data,const int& n, int& index)
	//{
	//	Element* New = new Element(Data);

	//	Element* Temp = Head;
	//	
	//	for (int i = 0; i < index-1; i++)
	//	{
	//		Temp = Temp->pNext;
	//	}
	//	New->pNext = Temp->pNext;
	//	Temp->pNext = New;
	//	/*for (int i = 0; index <= n; i++)
	//	{
	//		Temp = Temp->pNext;
	//	}*/
 //   }

	void insert(int Data,int index)
	{
		if (index == 0)return push_front(Data);
	
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
	/*	Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		
	

		size++;

	}
	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0)return pop_front();

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* erased = Temp->pNext;

		Temp->pNext = Temp->pNext->pNext;

		delete erased;
		size--;
	}

	//void erase(const int& n, int& index)
	//{
	//	Element* Temp = Head;
	//	Element* buffer;

	//	for (int i = 0; i <index; i++)
	//	{
	//		Temp = Temp->pNext;
	//	}
	//	Temp=nullptr;

	//	/*for (int i = index-1; i < index; i++)
	//	{
	//		Temp = Temp->pNext;
	//	}
	//	Temp = buffer;
	//	Temp->pNext = buffer->pNext;*/
	//}

	//  
	// 	     Methods:

	

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for(Element* Temp =Head; Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Кол-во элементов списка: " << size << endl;
		cout << "Общее кол-во элементов списка: " << Element::count << endl;
	}
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	
};

class Stack:ForwardList
{
public:
	const int& top()const
	{
		return Head->Data;
	}
	 int& top()
	{
		return Head->Data;
	}
	int push(int Data)
	{
		push_front(Data);
		return Head->Data;
	}
	int pop()
	{
		int Data = Head->Data;
		pop_front();
		return Data;
	}
	int size()const
	{
		return ForwardList::size;
	}
	bool empty()const
	{
		return Head == nullptr;
	}
	void swap(Stack& other)
	{
		Element* bufferHead = this->Head;
		this->Head = other.Head;
		other.Head = this->Head;

		int bufferSize =this->size();
		this->ForwardList::size = other.size();
		other.ForwardList::size = bufferSize;
	}
	void info()const
	{
		cout << this << ":\n";
		cout << "Size: " << size() << endl;
		for (int i : ForwardList(*this))cout << i<< tab; cout << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "Введите кол-во элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{

		list.push_front(rand() % 100);
	}
	int index, value;
	cout << "Введите индекс элемента: "; cin >> index;
	cout << "Введите значение элемента: "; cin >> value;
	list.print();
	list.push_back(123);
	list.print();
	list.push_front(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.insert(value, index);
	list.print();
	list.erase(index);
	list.print();
#endif // BASE_CHECK



#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите кол-во элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	cout << "List filed" << endl;
	//list.print();
	cout << "Making copy" << endl;
	ForwardList list2 = list;
	//list2.print();
	cout << "Copy DONE" << endl;
#endif // PERFORMANCE_CHECK


	//list.push_back(123);
	//list.print();

#ifdef RANGE_BASED_FROM_ARRAY
	int arr[] = { 3, 5, 8, 13, 21,34,55,89,144 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;


	
#endif // RANGE_BASED_FROM_ARRAY


	//ForwardList list = { 3, 5, 8, 13, 21 };
	////list.print();

	//for (int i : list)
	//{
	//	cout << i << tab;
	//}
	//cout << endl;

	Stack stack;
	
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	cout << stack.size()<<endl;
	/*while (!stack.empty())
	{
		cout << stack.pop() << tab;
	}*/
	Stack stack2;
	stack2.push(34);
	stack2.push(55);
	stack2.push(89);
	cout << stack2.size() << endl;
	stack.info();
	stack2.info();

	stack.swap(stack2);
	stack.info();
	stack2.info();


}
 