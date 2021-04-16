// nullptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <type_traits>

void foo(char *);
void foo(int);

int main() {
	if (std::is_same<decltype(NULL), decltype(0)>::value)
		std::cout << "NULL == 0" << std::endl;
	if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
		std::cout << "NULL == (void *)0" << std::endl;
	if (std::is_same<decltype(NULL), std::nullptr_t>::value)
		std::cout << "NULL == nullptr" << std::endl;
	foo(0); // will call foo(int)
	// foo(NULL); // doesn't compile
	foo(nullptr); // will call foo(char*)

	system("pause");

	return 0;
}

void foo(char *) {
	std::cout << "foo(char*) is called" << std::endl;
}
void foo(int i) {
	std::cout << "foo(int) is called" << std::endl;
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
