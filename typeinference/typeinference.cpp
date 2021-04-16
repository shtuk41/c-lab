// typeinference.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <initializer_list>
#include <vector>
#include <iostream>
#include <string>

class MagicFoo {
public:
	std::vector<int> vec;
	MagicFoo(std::initializer_list<int> list) {
		for (auto it = list.begin(); it != list.end(); ++it) {
			vec.push_back(*it);
		}
	}
};

template<typename R, typename T, typename U>
R add(T x, U y) {
	return x + y;
}

template<typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
	return x + y;
}

template<typename T, typename U>
auto add3(T x, U y) {
	return x + y;
}

std::string lookup1()
{
	return std::string("hello1");
}

std::string& lookup2()
{
	auto s = new std::string("hello2");

	return *s;
}

decltype(auto) look_up_a_string_1() {
	return lookup1();
}
decltype(auto) look_up_a_string_2() {
	return lookup2();
}

int main() {

	//auto

	MagicFoo magicFoo = { 1, 2, 3, 4, 5 };
	std::cout << "magicFoo: ";
	for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;

	auto i = 5.1; // i as int
	auto arr = new auto(10); // arr as int

	//decltype

	auto x = 1;
	auto y = 2;

	decltype(x + y) z;

	if (std::is_same<decltype(x), int>::value)
		std::cout << "type x == int" << std::endl;
	if (std::is_same<decltype(x), float>::value)
		std::cout << "type x == float" << std::endl;
	if (std::is_same<decltype(x), decltype(z)>::value)
		std::cout << "type z == type x" << std::endl;

	auto r = add<int, int>(4, 3);

	std::cout << r << std::endl;

	auto r2 = add2(14, 13);

	std::cout << r2 << std::endl;

	auto w = add2(1, 2.0); //same as auto w = add2<int, double>(1, 2.0); ?
	if (std::is_same<decltype(w), double>::value) {
		std::cout << "w is double: ";
	}
	std::cout << w << std::endl;

	auto r3 = add3(10, 11);

	std::cout << r3 << std::endl;

	auto q = add3<double, int>(1.0, 2);
	std::cout << "q: " << q << std::endl;

	//decltype(auto)

	auto s2 = look_up_a_string_2();

	std::cout << s2 << std::endl;

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
