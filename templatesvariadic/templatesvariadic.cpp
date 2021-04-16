// templatesvariadic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

template<typename T0>
void printf1(T0 value) {
	std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
	std::cout << value << std::endl;
	printf1(args...);
}

template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
	std::cout << t0 << std::endl;
	if constexpr (sizeof...(t) > 0) printf2(t...);
}

template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
	std::cout << value << std::endl;
	(void)std::initializer_list<T>{([&args] {
		std::cout << args << std::endl;
	}(), value)...};
}

template<typename ... T>
auto sum(T ... t) {
	return (t + ...);
}

template <auto value> void foo() {
	std::cout << value << std::endl;
	return;
}

int main() {
	printf1(1, 2, "123", 1.1);
	printf2(1, 2, "123", 1.1);
	printf3(1, 2, "123", 1.1);

	//fold
	std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;

	foo<10>();
	
	
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
