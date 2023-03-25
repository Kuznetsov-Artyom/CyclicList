#include <iostream>
#include "List.hpp"




template<typename T>
void printList(const List<T>& list)
{
	if (list.empty()) std::cout << "List is empty\n";
	else std::cout << "Elements list: " << list << '\n';
}



int main(int argc, char* argv[])
{
	List<int> list;

	for (int i = 0; i < 5; ++i)
		list.push_back(i + 1);


	List<int> listTwo;

	for (int i = 0; i < 3; ++i)
		listTwo.push_back(i + 1);

	printList(list);
	printList(listTwo);

	listTwo = list;

	printList(list);
	printList(listTwo);

	std::cout << "\n\n";



	return 0;
}