// SmartPointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i)
{
	(*i)++;
}

struct Foo 
{
	Foo() { std::cout << "Foo::Foo" << std::endl; }
	~Foo() { std::cout << "Foo::~Foo" << std::endl; }
	void foo() { std::cout << "Foo::foo" << std::endl; }
};

void f(const Foo &) 
{
	std::cout << "f(const Foo&)" << std::endl;
}

class A;
class B;

class A
{
public:
	std::shared_ptr<B> pointer;
	~A()
	{
		std::cout << "A was destroyed" << std::endl;
	}
};

class B
{
public:
	std::shared_ptr<A> pointer;
	~B()
	{
		std::cout << "B was destroyed" << std::endl;
	}
};

int main()
{
	std::cout << "\n Shared ptr \n" << std::endl;

	auto pointer = std::make_shared<int>(10);
	foo(pointer);
	std::cout << *pointer << std::endl;

	auto pointer2 = pointer; // reference count+1
	auto pointer3 = pointer; // reference count+1
	int *p = pointer.get(); // no increase of reference count
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 3
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

	pointer2.reset();
	std::cout << "reset pointer2:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 2
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0, pointer2 has reset
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
	pointer3.reset();
	std::cout << "reset pointer3:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 1
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 0, pointer3 has reset

	std::cout << "\n Unique ptr \n" << std::endl;

	std::unique_ptr<Foo> p1(std::make_unique<Foo>());

	// p1 is not empty, prints
	if (p1)
	{
		p1->foo();
	}

	{
		std::unique_ptr<Foo> p2(std::move(p1));
		// p2 is not empty, prints
		f(*p2);
		// p2 is not empty, prints
		if (p2) p2->foo();
		// p1 is empty, no prints
		if (p1) p1->foo();
		p1 = std::move(p2);
		// p2 is empty, no prints
		if (p2) p2->foo();
		std::cout << "p2 was destroyed" << std::endl;
	}

	// p1 is not empty, prints
	if (p1) p1->foo();
	// Foo instance will be destroyed when leaving the scope

	std::cout << "\n Weak ptr \n" << std::endl;

	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();

	a->pointer = b;
	b->pointer = a;

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
