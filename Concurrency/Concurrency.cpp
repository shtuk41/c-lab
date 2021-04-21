// Concurrency.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <queue>
#include <chrono>
#include <condition_variable>

int v = 1;

void critical_section(int change_v)
{
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

	v = change_v;
}

void critical_section_ul(int change_v)
{
	static std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);

	v = change_v;
	std::cout << v << std::endl;
	lock.unlock();

	lock.lock();
	v += 1;
	std::cout << v << std::endl;
}

int main()
{
	std::cout << "\n**** thread ****\n\n";
	std::thread t([]() {std::cout << "hello world." << std::endl; });
	t.join();

	std::cout << "\n**** lock_guard **** \n\n";

	std::thread t1(critical_section, 2), t2(critical_section, 3);
	t1.join();
	t2.join();

	std::cout << v << std::endl;

	std::cout << "\n**** unique_lock ****\n\n";

	v = 1;

	std::thread t1_ul(critical_section_ul, 2), t2_ul(critical_section_ul, 3);
	t1_ul.join();
	t2_ul.join();

	std::cout << "\n**** future ****\n\n";

	std::packaged_task<int()> task([]() {return 7; });

	std::future<int> result = task.get_future();
	std::thread(std::move(task)).detach();

	std::cout << "waiting...";
	result.wait();

	std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;

	std::cout << "\n**** condition variable ****\n\n";

	std::queue<int> produced_nums;
	std::mutex mtx;
	std::condition_variable cv;
	bool notified = false;

	auto producer = [&]()
	{
		for (int i = 0;; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::unique_lock<std::mutex> lock(mtx);
			std::cout << "producer locked mtx" << std::endl;
			std::cout << "producing " << i << std::endl;
			produced_nums.push(i);
			notified = true;
			std::cout << "notified all" << std::endl;
			cv.notify_all();
		}
	};

	auto consumer = [&](int thread_number) {
		while (true) {
			std::unique_lock<std::mutex> lock(mtx);
			std::cout << "thread " << thread_number << " locked mtx" << std::endl;
			while (!notified) { // avoid spurious wakeup
				std::cout << "thread " << thread_number << " about to wait" << std::endl;
				cv.wait(lock);
				std::cout << "thread " << thread_number << " wait" << std::endl;
			}
			// temporal unlock to allow producer produces more rather than
			// let consumer hold the lock until its consumed.
			std::cout << "thread " << thread_number << " unlock" << std::endl;
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // consumer is slower
			lock.lock();
			std::cout << "thread " << thread_number << " lock" << std::endl;
			if (!produced_nums.empty()) {
				std::cout << "consuming " << thread_number << " " << produced_nums.front() << std::endl;
				produced_nums.pop();
			}
			notified = false;
		}
	};

	std::thread p(producer);
	std::thread cs[2];

	for (int i = 0; i < 2; ++i)
	{
		cs[i] = std::thread(consumer, i);
	}

	p.join();
	for (int i = 0; i < 2; ++i)
	{
		cs[i].join();
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
