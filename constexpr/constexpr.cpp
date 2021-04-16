// constexpr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#define LEN 10

int len_foo()
{
	int i = 2;
	return i;
}

constexpr int len_foo_constexpr()
{
	return 0;
}

//legal C++11
/*constexpr int fibonacci(const int n)
{
	return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}*/

//c++14
constexpr int fibonacci(const int n) {
	if (n == 1) return 1;
	if (n == 2) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	char arr_1[10];

	char arr_2[LEN];

	int len = 10;

	//char arr_3[len]; //illegal

	const int len_2 = len + 1;

	constexpr int len_2_constexpr = 1 + 2 + 3;

	//char arr_4[len_2]; // illegal, but ok for most of the compilers
	char arr_4[len_2_constexpr]; // legal
	// char arr_5[len_foo()+5]; // illegal
	char arr_6[len_foo_constexpr() + 1]; // legal
	// 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
	std::cout << fibonacci(10) << std::endl;




    std::cout << "Hello World!\n"; 

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
