#include<iostream>
using namespace std;
#define tab "\t"

//#define BASE_CHECK
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
};

unsigned int Element::count = 0;
class ForwardList
{
	Element* Head;
	unsigned int size;
public: 
	ForwardList()
	{
		size = 0;
		Head = nullptr;
		cout << "LConstructor:\t\t\t" << this << endl;
	}

	/*ForwardList(std::initializer_list<int>il) :ForwardList()
	{
		
	}*/
	ForwardList(const ForwardList& other)
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
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
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

	//void reverse()
	//{
	//	ForwardList buffer;
	//	while (Head)
	//	{
	//		buffer.push_front(Head->Data);
	//		pop_front();
	//	}
	//	this->Head = buffer.Head;
	//	buffer.Head = nullptr;
	//}

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


	//list.push_back(123);
	//list.print();

 /*int arr[] = { 3, 5, 8, 13, 21,34};

 for (int i = 0;i<sizeof(arr)/sizeof(arr[0]); i++)
 {
	 cout << arr[i] << endl;
 }*/

	//ForwardList list ={ 3,5,8,13,21 };
	//list.print();

	int n;
	cout << "Введите кол-во элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	cout << "List filed" << endl;
	list.print();

	ForwardList list2 = list;
	list2.print();
}
