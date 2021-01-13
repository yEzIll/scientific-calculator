#pragma once
#include"header.h"
class Matrix
{
	friend ostream& operator<<(ostream&, const Matrix&);

private:
public:
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator/(const Matrix&);
	const Matrix& operator=(const Matrix& a);

	Matrix(int x, int y);
	~Matrix();
	double** el = NULL;
	int mx = 0;
	int my = 0;
};