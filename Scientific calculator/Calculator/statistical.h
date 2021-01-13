#pragma once
#ifndef STATISTICAL
#define STATISTICAL
#include"header.h"

template <class Type>
Type stringToNum(const string& str)
{
	istringstream ss(str);
	Type num;
	ss >> num;
	return num;
}

class Statistical {
public:
	Statistical() {}
	~Statistical(){}
	void run();
	void var_ave();
	void linear();
};
#endif