// function.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <functional>

using foo = void(int);

void functional_(foo f)
{
	f(1);
}

int foo_(int para)
{
	return para;
}

int foo__(int a, int b, int c, int d) {
	int ret = a + b + c + d;
	std::cout << ret << std::endl;
	return ret;
}

int main()
{
	auto f = [](int value) {
		std::cout << value << std::endl;
	};
	functional_(f); // call by function pointer
	f(1); // call by lambda expression


	std::function<int(int)> func = foo_;
	int important = 10;
	std::function<int(int)> func2 = [&](int value) -> int {
		return 1 + value + important;
	};
	std::cout << func(10) << std::endl;
	std::cout << func2(10) << std::endl;

	auto bindFoo = std::bind(foo__, std::placeholders::_1, std::placeholders::_2, 1, 2);

	bindFoo(5, 4);

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
