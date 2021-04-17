// delegateconstructor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

class Base
{
public:
	int value1;
	int value2;

	Base()
	{
		value1 = 1;
	}

	Base(int value) : Base() // delegate Base() constructor
	{
		value2 = value;
	}
};

class SubClass : public Base
{
public:
	using Base::Base; //inheritance constructor
};

int main()
{
	Base b(2);

    std::cout << b.value1 << std::endl;
	std::cout << b.value2 << std::endl;

	SubClass s(3);

	std::cout << s.value1 << std::endl;
	std::cout << s.value2 << std::endl;


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
