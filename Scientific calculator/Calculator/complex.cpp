//fig complex.cpp
#include"header.h"
#include"complex.h"
string stor(const double a, const int n);
string stor_com(const double a)
{
	ostringstream out;
	out << a;
	string b = out.str();
	while (b.size() > 8 && b[b.size() - 1] != '.')
	{
		b.erase(b.end() - 1);
		if (b.size() == 9 && isdigit(b[b.size() - 1]) && b[b.size() - 1] - '0' > 4)
		{
			b[16]++;
		}
	}
	return b;
}

complex::complex(double x, double y) :real(x), ima(y) {}
bool complex::operator==(const complex& a)const 
{ 
	return (real == a.real && ima == a.ima) ? true : false; 
}
bool complex::operator!=(const complex& a)const 
{ 
	return !(operator==(a)); 
}
complex complex::operator+(const complex& a)const
{
	return complex(real + a.real, ima + a.ima);
}
complex complex::operator-(const complex& a)const
{
	return complex(real - a.real, ima - a.ima);
}
complex complex::operator*(const complex& b)const {
	return complex(real * b.real - ima * b.ima, ima * b.real + real * b.ima);
}
complex complex::operator/(const complex& b)const {
	complex a(real, ima);
	complex c(b.real, -1 * b.ima);
	double k = pow(b.real, 2) + pow(b.ima, 2);
	complex tmp = a * c;
	tmp.real /= k; tmp.ima /= k;
	return tmp;
}
ostream& operator<<(ostream& output, const complex& a)
{
	if (a.real != 0 || a.ima == 0) output << a.real;
	if (a.ima != 0)
		if (a.ima < 0) {
			output << a.ima << "i";
		}
		else {
			if (a.real != 0)output << "+";
			output << a.ima << "i";
		}
	return output;
}
istream& operator>>(istream& input, complex& a) {
	input >> a.real >> a.ima; return input;
}
string com_str(const complex& a,int P)
{
		string x; 
		if (a.ima>=0)
		{
			x = stor(a.real, P) + "+" + stor(a.ima, P) + "i";
		}
		else
		{
			x = stor(a.real, P) + stor(a.ima, P) + "i";
		}
	return x;
}
string com_str_ans(const complex& a)
{
	string x;
	if (a.ima >= 0)
	{
		x = stor_com(a.real) + "+" + stor_com(a.ima) + "i";
	}
	else
	{
		x = stor_com(a.real) + stor_com(a.ima) + "i";
	}
	return x;
}
complex str_com(string a)
{
	if (a[0] == 'M') a.erase(a.begin());
	double real=0; double ima=0;
	istringstream ss1(a);
	ss1 >> real>>ima;
	return complex(real,ima);
}


#if 0
istream& operator>>(istream& input, complex& a) {
	input >> a.rec;
	int k = -1;
	for (int i = 0; i < a.rec.length(); i++)
	{
		if (!isdigit(a.rec[i]))
		{
			if (a.rec[i] == '+' || a.rec[i] == '-') { k = i; }//找到实虚部分界
			else if (a.rec[i] == 'i') {
				if (i != a.rec.length() - 1) {
					cin.setstate(ios::failbit);
					return input;
				}
			}//用以防止i后有数字
			else {
				cin.setstate(ios::failbit);
				return input;
			}//检查有无其他符号
		}
	}
	a.ima = 0; a.real = 0;
	if (k == -1)//解决A, Bi
	{
		if (a.rec[a.rec.length() - 1] == 'i')
		{
			for (int i = 0; i < a.rec.length() - 1; i++)
			{
				a.ima = a.ima * 10 + a.rec[i] - '0';
			}
		}
		else//说明是实数
		{
			for (int i = 0; i < a.rec.length(); i++)
			{
				a.real = a.real * 10 + a.rec[i] - '0';
			}
		}
	}
	else if (k == 0)//解决+-A与+-Bi
	{
		if (a.rec[a.rec.length() - 1] == 'i')
		{
			for (int i = 1; i < a.rec.length() - 1; i++)
			{
				a.ima = a.ima * 10 + a.rec[i] - '0';
			}
			if (a.rec[0] == '-') { a.ima *= -1; }
		}
		else
		{
			for (int i = 1; i < a.rec.length(); i++)
			{
				a.real = a.real * 10 + a.rec[i] - '0';
			}
			if (a.rec[0] == '-') { a.real *= -1; }
		}
	}
	else//解决A+-Bi与+-A+-Bi
	{
		if (isdigit(a.rec[0]))
		{
			for (int i = 0; i <= k - 1; i++)
			{
				a.real = a.real * 10 + a.rec[i] - '0';
			}
			for (int j = k + 1; j < a.rec.length() - 1; j++)
			{
				a.ima = a.ima * 10 + a.rec[j] - '0';
			}
			if (a.rec[k] == '-') { a.ima *= -1; }
		}
		else
		{
			for (int i = 1; i <= k - 1; i++)
			{
				a.real = a.real * 10 + a.rec[i] - '0';
			}
			if (a.rec[0] == '-') { a.real *= -1; }
			for (int j = k + 1; j < a.rec.length() - 1; j++)
			{
				a.ima = a.ima * 10 + a.rec[j] - '0';
			}
			if (a.rec[k] == '-') { a.ima *= -1; }
		}
	}
	return input;
}
#endif
