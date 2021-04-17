// forward.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <iostream>
#include <utility>
void reference(int& v) {
	std::cout << "lvalue reference" << std::endl;
}

void reference(int&& v) {
	std::cout << "rvalue reference" << std::endl;
}

template <typename T>
void pass(T&& v) {
	std::cout << " normal param passing: ";
	reference(v);
	std::cout << " std::move param passing: ";
	reference(std::move(v));
	std::cout << " std::forward param passing: ";
	reference(std::forward<T>(v));
	std::cout << "static_cast<T&&> param passing: ";
	reference(static_cast<T&&>(v));
}

int main() {
	std::cout << "rvalue pass:" << std::endl;
	pass(1);
	std::cout << "lvalue pass:" << std::endl;
	int l = 1;
	pass(l);
	return 0;
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
