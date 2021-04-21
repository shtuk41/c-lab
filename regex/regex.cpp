// regex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <regex>

int main()
{
	std::string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt","AAA.txt"};

	std::regex txt_regex("[a-z]+\\.txt");
	for (const auto &fname : fnames)
	{
		std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
	}

	std::regex base_regex("([a-z]+)\\.txt");
	std::smatch base_match;

	for (const auto &fname : fnames) {
		if (std::regex_match(fname, base_match, base_regex)) {
			// the first element of std::smatch matches the entire string
			// the second element of std::smatch matches the first expression with brackets
			if (base_match.size() == 2) {
				std::string base = base_match[1].str();
				std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
				std::cout << fname << " sub-match[1]: " << base << std::endl;
			}
		}
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
