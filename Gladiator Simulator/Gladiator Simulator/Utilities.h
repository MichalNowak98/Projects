#pragma once
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <memory>
#include <vector>

int random_int(int lower_limit, int upper_limit);

template<class T>
class Smart_container
{
	std::vector<std::unique_ptr<T>> vector;
public:
	Smart_container(T * _head);
	void push_back(T *_head);
};

template<class T>
inline Smart_container<T>::Smart_container(T * _head)
{
	this->push_back(_head);
}

template<class T>
inline void Smart_container<T>::push_back(T * _head)
{
	vector.push_back(std::unique_ptr<T>(_head));
}
