#pragma once
#include "myInclude.h"
template <class T>
class Singletone
{
public:
	static  T& getInstance()
	{
		static T instance;
		return instance;
	}
};