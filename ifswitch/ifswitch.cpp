// ifswitch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> vec = { 1,2,3, 2, 4 };

	// since c++17, can be simplified by using `auto`
	const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
	if (itr != vec.end()) 
	{
		*itr = 3;
	}

	for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
		std::cout << *element << std::endl;

	if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) 
	{
		*itr = 4;
	}

	// should output: 1, 4, 3, 4. can be simplified using `auto`
	for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); ++element)
		std::cout << *element << std::endl;

	system("puuse");
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
