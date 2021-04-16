
#include "pch.h"
#include "templates.h"
#include <iostream>


//template functions 
template<typename T>
myTemplate<T>::myTemplate()
	:data()
{
}

template<typename T>
myTemplate<T>::myTemplate(T t)
	: data(t)
{
}

template <typename T>
T myTemplate<T>::getData() const
{
	return data;
}

template <typename T>
void myTemplate<T>::displayData() const
{
	std::cout << data << std::endl;
}


template<typename T>
int myTemplate<T>::someValue = 100;


//The explicit instantiation part
template class myTemplate<int>;
template class myTemplate<float>;