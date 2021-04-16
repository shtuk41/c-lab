// initializerlist.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <initializer_list>
#include <vector>
class MagicFoo {
public:
	std::vector<int> vec;
	MagicFoo(std::initializer_list<int> list) {
		for (std::initializer_list<int>::iterator it = list.begin();
			it != list.end(); ++it)
			vec.push_back(*it);
	}

	void foo(std::initializer_list<int> list) {
		for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
			vec.push_back(*it);
	}
};


int main() {
	// after C++11
	MagicFoo magicFoo = { 1, 2, 3, 4, 5 };

	magicFoo.foo({ 6, 7, 8, 9 });
	
	std::cout << "magicFoo: ";
	
	for (std::vector<int>::iterator it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it)
		std::cout << *it << std::endl;

	MagicFoo foo2{ 3, 4 };

	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
