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
	List<std::string> list;

	printList(list);

	list.push_back("12333");
	list.push_back("lelle");
	list.push_back("123");
	list.push_back("00030030333");

	if (list.find("123"))
		std::cout << "TRUE\n";


	

	printList(list);

	list.pop_back();

	printList(list);

	list.push_front("100");

	printList(list);

	list.pop_front();

	printList(list);

	List<std::string> listTwo(list);

	printList(listTwo);




	return 0;
}