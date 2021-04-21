// atomic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> count = { 0 };

struct A
{
	float x;
	int y;
	long long z;
};

int main()
{
	std::cout << "**** atomic ****\n" << std::endl;

	std::thread t1([]() { count.fetch_add(1);  });

	std::thread t2([]() {  count++; count += 1; });

	t1.join();
	t2.join();
	std::cout << count << std::endl;

	std::cout << "**** checks if object will not cause threads to be blocked ****\n" << std::endl;

	std::atomic<A> a;
	std::cout << std::boolalpha << a.is_lock_free() << std::endl;

	std::cout << "**** Memory order ****\n" << std::endl;

	std::atomic<int> counter = { 0 };
	std::vector<std::thread> vt;

	for (int i = 0; i < 100; ++i)
	{
		vt.emplace_back([&]() {
			counter.fetch_add(1, std::memory_order_relaxed);
		});
	}

	for (auto &t : vt)
	{
		t.join();
	}

	std::cout << "current counter: " << counter << std::endl;

	std::cout << "**** Release /  consumption model ****\n" << std::endl;

	std::atomic<int*> ptr(nullptr);

	int v;

	std::thread producer([&]() {
		int *p = new int(42);
		v = 1024;
		ptr.store(p, std::memory_order_release);
	});

	std::thread consumer([&]() {
		int *p;
		while (!(p = ptr.load(std::memory_order_consume)));

		std::cout << "p: " << *p << std::endl;
		std::cout << "v: " << v << std::endl;
	});

	producer.join();
	consumer.join();

	std::cout << "**** Release /  acquire model ****\n" << std::endl;

	std::vector<int> ve;

	std::atomic<int> flag = { 0 };

	std::thread release([&]() {
		ve.push_back(42);
		flag.store(1, std::memory_order_release);

	});

	std::thread acqrel([&]()
	{
		int expected = 1;

		while (!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
			expected = 1; // must after compare_exchange_strong
		}
		
	});

	std::thread acquire([&]() {
		while (flag.load(std::memory_order_acquire) < 2);
		std::cout << ve.at(0) << std::endl; // must be 42
	});
	release.join();
	acqrel.join();
	acquire.join();

	std::cout << "**** Sequential Consistent Model ****\n" << std::endl;

	std::atomic<int> counter2 = { 0 };
	std::vector<std::thread> vt2;
	for (int i = 0; i < 100; ++i)
	{
		vt2.emplace_back([&]()
		{
			counter2.fetch_add(1, std::memory_order_seq_cst);
		});
	}

	for (auto &t : vt2)
	{
		t.join();
	}

	std::cout << "current counter: " << counter2 << std::endl;




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
