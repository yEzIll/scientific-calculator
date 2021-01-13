#pragma once
//fig complex.h
#include<iostream>
using namespace std;
#ifndef complex_h
#define complex_h
class complex
{
	friend ostream& operator<<(ostream&, const complex&);
	friend istream& operator>>(istream&, complex&);
public:
	explicit complex(double = 0.0, double = 0.0);
	complex operator+(const complex&) const;
	complex operator-(const complex&) const;
	complex operator*(const complex&)const;
	complex operator/(const complex&)const;
	bool operator==(const complex& a)const;
	bool operator!=(const complex& a)const;
	double real; double ima;
};
#endif