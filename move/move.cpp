// move.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <utility> // std::move
#include <vector> // std::vector
#include <string> // std::string

class A {
public:
	int *pointer;
	A() :pointer(new int(1)) {
		std::cout << "construct" << pointer << std::endl;
	}
	A(A& a) :pointer(new int(*a.pointer)) {
		std::cout << "copy" << pointer << std::endl;
	} // meaningless object copy
	A(A&& a) :pointer(a.pointer) {
		a.pointer = nullptr;
		std::cout << "move" << pointer << std::endl;
	}
	~A() {
		std::cout << "destruct" << pointer << std::endl;
		delete pointer;
	}
};
// avoid compiler optimization
A return_rvalue(bool test) {
	A a, b;
	if (test) return a; // equal to static_cast<A&&>(a);
	else return b; // equal to static_cast<A&&>(b);
}

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
}

int main()
{
	{
		A obj = return_rvalue(false);
		std::cout << "obj:" << std::endl;
		std::cout << obj.pointer << std::endl;
		std::cout << *obj.pointer << std::endl;
	}

	{
		//part 2
		std::string str = "Hello world.";
		std::vector<std::string> v;
		// use push_back(const T&), copy
		v.push_back(str);
		// "str: Hello world."
		std::cout << "str: " << str << std::endl;
		// use push_back(const T&&), no copy
		// the string will be moved to vector, and therefore std::move can reduce copy cost
		v.push_back(std::move(str));
		// str is empty now
		std::cout << "str: " << str << std::endl;
	}

	{
		std::cout << "rvalue pass:" << std::endl;
		pass(1);
		std::cout << "lvalue pass:" << std::endl;
		int l = 1;
		pass(l);
	}


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
