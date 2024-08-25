#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n-----------------------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor: \t" <<this <<endl;
		}
		~Element()
		{
			cout << "EDestructor: \t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		//while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//            Adding elements:
	void push_front(int Data)
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
	void push_back(int Data)
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
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
    else{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
		size--;
	}
	void pop_back()
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
	void insert(int Data,int index)
	{
		Element* New = new Element(Data);
		if (index == 0)return push_front(Data);
		if (size <= index)return push_back(Data);
	
		
		if (index < size/2)
		{
			Element* Temp = Head;
			for (int i = 0; i < index ; i++)Temp = Temp->pNext;
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev = New;
			Temp->pPrev->pPrev->pNext = New;
		}
		else
		{
			Element* Temp = Tail;
			for (int i = 0; i < (size - index) -1; i++)Temp=Temp->pPrev;
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev = New;
			Temp->pPrev->pPrev->pNext = New;
		}
		size++;
	}
	void erase(int index)
	{
		
		if (index == 0)return pop_front();
		if (index>size)return pop_back();

		
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
			
			for (int i = 0; i < (size - index)-1; i++)Temp=Temp->pPrev;
			Element* erased = Temp;
			Temp->pNext->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = Temp->pNext;
			delete erased;
		}
		size--;

	}
	//         Methods:
	void print()const
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
	void reverse_print()const
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
};

void main()
{
	setlocale(LC_ALL, "");
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

	
}