// templates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

template<typename T, typename U>
class MagicType {
public:
	T dark;
	U magic;
};

typedef int(*process)(void *);
using NewProcess = int(*)(void *);
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

template<typename T = double, typename U = double>
auto add(T x, U y) -> decltype(x + y) {
	return x + y;
}

int main()
{
	TrueDarkMagic<bool> you;

	you.dark.push_back(true);
	you.dark.push_back(false);
	you.magic = "hello";

	for (auto it : you.dark)
	{
		std::cout << it << std::endl;
	}

	auto r = add(4, 5); //not double?

	std::cout << r << std::endl;

	if (std::is_same<decltype(r), double>::value)
	{
		std::cout << "r is double" << std::endl;
	}
	else
	{
		std::cout << "r is not double" << std::endl;
	}


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
