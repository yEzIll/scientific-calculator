#pragma once
#ifndef CALCU
#define CALCU
#include"header.h"

class Calculate {
private:
	string sym = "+-*/!^";
public:
	double pri(string);
	Calculate();
	~Calculate();
	vector<string> c1;//存后缀表达式
	vector<string> c2;//临时栈
	int run();//返回change给main
	int b_reception();
	
	bool tiny(double x);//判断三角是否足够小可以输出0；
	//乘方，pow(m,n)
	//开跟，pow(m,1/n)
	string fac(int,int);//阶乘函数！及！！,不引发减号变化,超大数
	void cal_cal(vector<string> x,unsigned int);
	//三角,

};
#endif