#pragma once

#include <vector>
template <typename T>
class Array
{
	public:
	
	T* ptr;
	int size;
	
	Array();
	Array(T* ptr, int size);
	Array(std::vector<T> vec);
	T operator[](int i) const;
	T& operator[](int i);
};

template<typename T>
inline Array<T>::Array()
{
	this->ptr = nullptr;
	this->size = 0;
}

template<typename T>
inline Array<T>::Array(T* ptr, int size)
{
	this->ptr = ptr;
	this->size = size;
}

template<typename T>
inline Array<T>::Array(std::vector<T> vec)
{
	this->ptr = &vec[0];
	this->size = vec.size();
}

template<typename T>
inline T Array<T>::operator[](int i) const
{
	return ptr[i];
}

template<typename T>
inline T& Array<T>::operator[](int i)
{
	return ptr[i];
}
