#pragma once

template <typename U, typename V, typename R>
R add(U a, V b)
{
	return a + b;
}

template <typename T>
class myTemplate
{
private:
	T data;


public:
	myTemplate();
	myTemplate(T t);
	T getData() const;
	void displayData() const;

	static int someValue;

};
