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
	vector<string> c1;//���׺���ʽ
	vector<string> c2;//��ʱջ
	int run();//����change��main
	int b_reception();
	
	bool tiny(double x);//�ж������Ƿ��㹻С�������0��
	//�˷���pow(m,n)
	//������pow(m,1/n)
	string fac(int,int);//�׳˺�����������,���������ű仯,������
	void cal_cal(vector<string> x,unsigned int);
	//����,

};
#endif