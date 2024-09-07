#include "List.cpp"

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

	List<std::string> s_list = { "хорошо" ,"живёт" ,"на", "свете" };
	for (std::string i : s_list)cout << i << tab;
	cout << endl;

}