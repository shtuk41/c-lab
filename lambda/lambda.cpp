// lambda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

void lambda_value_capture() {
	int value = 1;
	auto copy_value = [value] {
		return value;
	};
	value = 100;
	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// At this moment, stored_value == 1, and value == 100.
	// Because copy_value has copied when its was created.
}

void lambda_reference_capture() {
	int value = 1;
	int value2 = 2;
	auto copy_value = [&, value] {
		return value + value2;
	};
	value = 100;
	value2 = 200;
	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// At this moment, stored_value == 100, value == 100.
	// Because copy_value stores reference
}

void lambda_expression_capture() {
	auto important = std::make_unique<int>(1);
	auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
		return x + y + v1 + (*v2);
	};
	std::cout << add(3, 4) << std::endl;
}

void lambda_generic() {
	auto generic = [](auto x, auto y) {
		return x + y;
	};

	std::cout << generic(1, 2) << std::endl;
	std::cout << generic(1.1, 2.2) << std::endl;
}

int main()
{
	lambda_value_capture();

	lambda_reference_capture();

	lambda_expression_capture();

	lambda_generic();

	
 
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
