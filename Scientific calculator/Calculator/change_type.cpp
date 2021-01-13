#include"basis.h"
double str_dou(string x)//默认模式
{
	double num;
	istringstream ss1(x);
	ss1>> num;
	return num;
}
int str_int(string x)//默认模式
{
	int num;
	istringstream ss1(x);
	ss1 >> num;
	return num;
}
void str_char(char(*a)[20], string s)
{
	istringstream iss(s);
	iss >> *a;
}
string char_str(char a[20])
{
	stringstream ss;
	ss << a;
	return ss.str();
}
string stor(const double a, const int n)
{
	ostringstream out;
	out << fixed << setprecision(n) << a;
	string b = out.str();
	while (b.size() > 17 && b[b.size() - 1] != '.')
	{
		b.erase(b.end() - 1);
		if (b.size() == 18 && isdigit(b[b.size() - 1]) && b[b.size() - 1] - '0' > 4)
		{
			b[16]++;
		}
	}
	return b;
}


//进制
string _2_10(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int integer = 0; double dou = 0.0;
	for (int i = 0; i < a.size(); i++)
	{
		integer += ((unsigned __int64)a[i] - '0') * pow(2, a.size() - i - 1);
	}
	for (int i = 0; i < b.size(); i++)
	{
		dou += ((unsigned __int64)b[i] - '0') * pow(2, -1 - i);
	}
	return stor(sign * (integer + dou), P);
}
string _10_2(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	b = "0." + b;

	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int a1 = str_int(a);
	string b1 = "";
	for (; a1 != 0; a1 = a1 / 2)
	{
		b1 = stor(a1 % 2, 0)+b1;
	}
	double a2 = str_dou(b);
	string b2 = "";
	for (; a2 != 0 && b2.size() < P;)
	{
		a2 = a2 * 2;
		if (a2 >= 1)
		{
			a2 -= 1;
			b2 = b2 + "1";
		}
		else
		{
			b2 = b2 + "0";
		}
	}
	if (b1 == "") b1 = "0";
	string b3 = b1 + "." + b2;
	if (sign == -1) b3 = "-" + b3;
	return b3;
}
string _8_10(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int integer = 0; double dou = 0.0;
	for (int i = 0; i < a.size(); i++)
	{
		integer += ((unsigned __int64)a[i] - '0') * pow(8, a.size() - i - 1);
	}
	for (int i = 0; i < b.size(); i++)
	{
		dou += ((unsigned __int64)b[i] - '0') * pow(8, -1 - i);
	}
	return stor(sign * (integer + dou), P);
}
string _10_8(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	b = "0." + b;

	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int a1 = str_int(a);
	string b1 = "";
	for (; a1 != 0; a1 = a1 / 8)
	{
		b1 = stor(a1 % 8, 0) + b1;
	}
	double a2 = str_dou(b);
	string b2 = "";

	for (; a2 != 0 && b2.size() < P;)
	{
		a2 = a2 * 8;
		b2 = b2 + stor((int)a2, 0);
		a2 -= (int)a2;
	}
	if (b1 == "") b1 = "0";
	string b3 = b1 + "." + b2;
	if (sign == -1) b3 = "-" + b3;
	return b3;
}

string _10_16(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	b = "0." + b;

	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int a1 = str_int(a);
	string b1 = "";
	for (; a1 != 0; a1 = a1 / 16)
	{
		int temp = a1 % 16;
		string k;
		switch (temp) {
		case(10): k = "A"; break;
		case(11): k = "B"; break;
		case(12): k = "C"; break;
		case(13): k = "D"; break;
		case(14): k = "E"; break;
		case(15): k = "F"; break;
		default:  k = stor(a1 % 16, 0);
		}
		b1 = k + b1;
	}
	double a2 = str_dou(b);
	string b2 = "";
	for (; a2 != 0 && b2.size() < P;)
	{
		a2 = a2 * 16;
		int temp = (int)a2;
		string k;
		switch (temp) {
		case(10): k = "A"; break;
		case(11): k = "B"; break;
		case(12): k = "C"; break;
		case(13): k = "D"; break;
		case(14): k = "E"; break;
		case(15): k = "F"; break;
		default:  k = stor((int)a2, 0);
		}
		b2 = b2 + k;
		a2 -= (int)a2;
	}
	if (b1 == "") b1 = "0";
	string b3=b1 + "." + b2;
	if (sign == -1) b3 = "-" + b3;
	return b3;
}

string _16_10(string x, int P)
{
	stringstream f(x);
	string a, b;
	getline(f, a, '.');//将cin中的数据赋值给a;
	getline(f, b);//将f中直到；前的字符串赋值给b（如同输入流）
	f.clear();//清空f流
	int sign = 1;
	if (a[0] == '-')
	{
		a.erase(a.begin());
		sign = -1;
	}

	int integer = 0; double dou = 0.0;
	for (int i = 0; i < a.size(); i++)
	{
		char k = a[i];
		int tmp;
		switch (k) {
		case('A'): tmp = 10; break;
		case('B'): tmp = 11; break;
		case('C'): tmp = 12; break;
		case('D'): tmp = 13; break;
		case('E'): tmp = 14; break;
		case('F'): tmp = 15; break;
		default:  tmp = k - '0';
		}
		integer += tmp * pow(16, a.size() - i - 1);
	}
	for (int i = 0; i < b.size(); i++)
	{
		char k = b[i];
		int tmp;
		switch (k) {
		case('A'): tmp = 10; break;
		case('B'): tmp = 11; break;
		case('C'): tmp = 12; break;
		case('D'): tmp = 13; break;
		case('E'): tmp = 14; break;
		case('F'): tmp = 15; break;
		default:  tmp = k - '0';
		}
		dou += tmp * pow(16, -1 - i);
	}
	return stor(sign * (integer + dou), P);
}

//判断是否输出0
bool Calculate::tiny(double x)
{
	if (abs(x) < 0.0000000001)
		return true;
	else return false;
}
//判断string中是否是数字，用于calcal
bool isnum(string x) {
	double num; string nums;
	istringstream ss1(x);
	if (ss1 >> num)
	{
		if (ss1 >> nums) return false;
		return true;
	}
	return false;
}
