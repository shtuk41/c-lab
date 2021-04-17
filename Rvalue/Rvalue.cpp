// Rvalue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <chrono>
#include <string>
#include "X.h"
using namespace std::chrono;

void process_copy_lvalue(std::vector<int> const &vec_)
{
	std::vector<int> vec(vec_);
	vec.push_back(42);
}

void process_copy_rvalue(std::vector<int> && vec_)
{
	vec_.push_back(42);
}

void do_stuff(X&& x_)
{
	//inside function x_ is treated like lvalue
	X a(x_);
	X b(std::move(x_));
}

template<typename T>
void foo(T&& t)
{

}

void reference(std::string& str) {
	std::cout << "lvalue" << std::endl;
}
void reference(std::string&& str) {
	std::cout << "rvalue" << std::endl;
}

int main()
{
	/******************part 1*****************/
	int var = 42;
	int &ref = var;
	ref = 99;
	assert(var == 99);

	int const &i = 42; //const reference to rvalue allowed
	int &&j = 42;	//rvalue

	/******************part 2*****************/
	std::vector<int> v;
	for (int ii = 0; ii < 1000000; ii++)
	{
		v.push_back(ii);
	}

	//copy to function, not touching the original
	
	auto start = high_resolution_clock::now();
	
	process_copy_lvalue(v);

	auto stop = high_resolution_clock::now();

	std::cout << v.size() << std::endl;

	auto duration = duration_cast<microseconds>(stop - start); //this takes 4300 microseconds
	std::cout << duration.count() << std::endl;


	std::cout << v.size() << std::endl;


	start = high_resolution_clock::now();
	process_copy_rvalue(std::move(v));

	stop = high_resolution_clock::now();

	duration = duration_cast<microseconds>(stop - start); //this takes 3 microseconds
	std::cout << duration.count() << std::endl;

	std::cout << v.size() << std::endl;

	/******************part 3*****************/

	X x1;
	X x2 = std::move(x1);
	//X x3 = static_cast<X&&>(x2);
	do_stuff(std::move(x2));

	//x2.update(); //x2 data is nullptr


	/******************part 4*****************/

	//rvalue
	foo(42); //call foo<int>(42)
	foo(3.14159);//calls foo<double>(3.14159)
	foo(std::string()); //calls foo<std::string>(std::string())

	//lvalue
	int iii = 42;
	foo(iii); //calls foo<int&> this is treated as reference to a reference to lvalue

	//part 5 c++ on a fly
	std::string lv1 = "string,"; // lv1 is a lvalue
	// std::string&& r1 = s1; // illegal, rvalue can't ref to lvalue
	std::string&& rv1 = std::move(lv1); // legal, std::move can convert lvalue to rvalue
	std::cout << rv1 << std::endl; // string

	const std::string& lv2 = lv1 + lv1; // legal, const lvalue reference can extend temp variable's lifecycle
// lv2 += "Test"; // illegal, const ref can't be modified
	std::cout << lv2 << std::endl; // string,string
	std::string&& rv2 = lv1 + lv2; // legal, rvalue ref extend lifecycle
	rv2 += "string"; // legal, non-const reference can be modified
	std::cout << rv2 << std::endl; // string,string,string,string
	reference(rv2); // output: lvalue





	std::cout << "endl" << std::endl;
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
