// Containers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <array>
#include <string>
#include <unordered_map>
#include <map>
#include <tuple>
#include <variant>

void foo(int *p, int len)
{
	return;
}

auto get_student(int id)
{
	if (id == 0)
	{
		return std::make_tuple(3.8, 'A', "John");
	}
	if (id == 1)
	{
		return std::make_tuple(2.9, 'C', "Jack");
	}
	if (id == 2)
	{
		return std::make_tuple(1.7, 'D', "Ive");
	}

	return std::make_tuple(0.0, 'D', "null");
}

template<size_t n, typename... T>
constexpr std::variant <T...> _tuple_index(const std::tuple<T...> &tp1, size_t i)
{
	if constexpr (n >= sizeof...(T))
		throw std::out_of_range(" .");
	if (i == n)
	{
		return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tp1)};
	}

	return _tuple_index<(n < sizeof...(T) - 1 ? n + 1 : 0)>(tp1, i);
}

template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
	return _tuple_index<0>(tpl, i);
}
template <typename T0, typename ... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
	std::visit([&](auto && x) { s << x; }, v);
	return s;
}

template <typename T>
auto tuple_len(T &tpl) {
	return std::tuple_size<T>::value;
}

int main()
{
	std::array<int, 4> arr = { 1,5,3,4 };

	if (arr.empty())
	{
		std::cout << "container is empty" << std::endl;
	}
	else
	{
		std::cout << "Container size is " << arr.size() << std::endl;
	}

	for (auto &i : arr)
	{
		std::cout << i << std::endl;
	}

	std::sort(arr.begin(), arr.end(), [](int a, int b) {return b > a; });

	for (auto &i : arr)
	{
		std::cout << i << std::endl;
	}

	constexpr int len = 4;
	std::array<int, len> arr2 = { 1,2,3,4 };

	foo(&arr2[0], arr2.size());
	foo(arr2.data(), arr2.size());

	std::sort(arr2.begin(), arr2.end());

	//std::forward_list - like list but only single linked list

	std::cout << "\nUnordered container \n" << std::endl;

	std::unordered_map<int, std::string> u =
	{
		{1,"1"},
		{3,"3"},
		{2, "2"}
	};

	std::map<int, std::string> v =
	{
		{1, "1"},
		{3, "3"},
		{2, "2"}
	};

	std::cout << "std::unordered_map" << std::endl;

	for (const auto & n : u)
	{
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
	}

	std::cout << std::endl;
	std::cout << "std::map" << std::endl;
	for (const auto & n : v)
	{
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
	}

	std::cout << "\nTuple \n" << std::endl;

	auto student = get_student(0);
	std::cout << "ID: 0, "
		<< "GPA: " << std::get<0>(student) << ", "
		<< "Grade: " << std::get<1>(student) << ", "
		<< "Name: " << std::get<2>(student) << '\n';

	double gpa;
	char grade;
	std::string name;

	std::tie(gpa, grade, name) = get_student(1);
	std::cout << "ID: 1, "
		<< "GPA: " << gpa << ", "
		<< "Grade: " << grade << ", "
		<< "Name: " << name << "\n";

	std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
	std::cout << std::get<std::string>(t) << std::endl;
	//std::cout << std::get<double>(t) << std::endl; // illegal, runtime error
	std::cout << std::get<3>(t) << std::endl;

	std::cout << "\n Variant \n" << std::endl;

	int i = 1;
	std::cout << tuple_index(t, i) << std::endl;

	std::cout << "\n Merge and Iteration \n" << std::endl;

	std::tuple<std::string, double, double, int> new_tuple("123", 4.5, 6.7, 8);

	for (int i = 0; i != tuple_len(new_tuple); ++i)
	{
		std::cout << tuple_index(new_tuple, i) << std::endl;
	}
	

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
