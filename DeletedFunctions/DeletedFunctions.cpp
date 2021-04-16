// DeletedFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#include "no_copies.h"
#include "copies.h"
#include "move_only.h"

template <class T>
void some_function(T h)
{
	std::cout << h << std::endl;
}

void some_function(int t) = delete;

int main()
{
	//part 1
	copies copies_1;

	copies copies_2 = copies_1;//good
	copies copies_3(copies_1);//good

	no_copies no_copies_1;
	//no_copies no_copies_2 = no_copies_1; //not allowed
	//no_copies no_copies_3(no_copies_1);// not allowed

	//part 2
	move_only m1;
	//move_only m2(m1); //constructor deleted
	move_only m3(std::move(m1));

	//part 3
	some_function("Hello");
	//some_function(int(3));//compile error  - attempt to use deleted function

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
