#include"statistical.h"
#include"setting.h"
using namespace std;
int var_reception();
void menu1_1_1();
void Statistical::var_ave() {
	menu1_1_1();
	while (true)
	{
		int exit = 0; bool exit2 = false;

		vector<double>x;
		double temp = 0.0;
		double sum = 0.0;
		cout << ">>>";
		while (true) {
			int choice = var_reception();
			switch (choice)
			{
			case (1):
				exit2 = true;
				break;
			case (2):
				cin >> temp;
				sum += temp;
				x.push_back(temp);
				break;
			case (3):
				exit = 1;//�����ϼ��˵�
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//������棬��������
				system("cls");
				menu1_1_1();
				break;
			default:
				cerr << "���������������������" << endl;
				exit = 2;
				break;
			}
			if (exit != 0 || exit2) break;
		}
		if (exit == 1)
		{
			break;
		}
		else if (exit == 2 || x.size() == 0) continue;

		double var = 0.0;
		double ave = sum / x.size();
		for (int i = 0; i < x.size(); i++) {
			var += (x[i] - ave) * (x[i] - ave) / x.size();
		}

		cout << "���У�" << x.size() << "������" << endl;
		cout << "ƽ����:" << ave << endl;
		cout << "����" << var << endl << endl;
	}
}
int var_reception() {
	while (true)
	{
		if (cin.peek() == '\n')
		{
			cin.ignore();
			return 1;//��ʼ����
		}
		else if (cin.peek() == ' ') {
			cin.ignore();
		}
		else if (isdigit(cin.peek())) return 2;
		else if (cin.peek() == '-')
		{
			cin.ignore();
			if (isdigit(cin.peek())) return 6;
			cin.ignore(255, '\n');
			return 5;
		}
		else if (cin.peek() == 'Q')
		{
			cin.ignore();
			return 3;
		}
		else if (cin.peek() == 'W')
		{
			cin.ignore(255, '\n');
			return 4;
		}
		else
		{
			cin.ignore(255, '\n');
			return 5;
		}
	}
}
void menu1_1_1() {
	cout << ">>>�˳�����������Q......" << endl;
	cout << ">>>�������������W......" << endl;
	cout << ">>>��������������,�ÿո�ֿ����س���ʼ���㡣" << endl;
	cout << ">>>����123 456 789" << endl;
}

void menu1_1_2() {
	cout << ">>>�˳�����������Q......" << endl;
	cout << ">>>�������������W......" << endl;
}
void Statistical::linear()
{
	menu1_1_2();
	while (true)
	{
		int exit = 0; bool exit2 = false;
		int parity = 1; double n=0;
		vector<double>y; vector<double>x;
		double temp = 0.0;
		double sumx = 0.0, sumy = 0.0;
		cout << "��������Ϸ���ϵ��n,��-1�����y=ax^-1 +b�������"<<endl;
		cout << ">>>";
		while (true) {

			int choice = var_reception();
			switch (choice)
			{
			case (1):
				exit2 = true;
				break;
			case (2):
			{
				cin >> n;
				break;
			}
			case(6):
			{
				cin >> n;
				n = n * -1;
				break;
			}
			case (3):
				exit = 1;//�����ϼ��˵�
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//������棬��������
				system("cls");
				menu1_1_2();
				break;
			case(5):
				cerr << "���������������������" << endl;
				exit = 2;
				break;
			}
			if (exit != 0 || exit2) break;
		}
		if (exit == 1)
		{
			break;
		}
		else if (exit == 2) continue;

		exit2 = false;
		cout << ">>>����������n���,�ÿո�ֿ�����ʽ���£��س���ʼ���㡣" << endl;
		cout << ">>>�����㼯(3,2),(4 1) ���� 3 2 4 1" << endl<<">>>";
		while (true) {
			int choice = var_reception();
			switch (choice)
			{
			case (1):
				exit2 = true;
				break;
			case (2):
			{
				cin >> temp; double ele;
				if (parity == 1)
				{
					ele = pow(temp, n);
					sumx += ele;
					x.push_back(ele);
					parity++;
				}
				else
				{
					sumy += temp;
					y.push_back(temp);
					parity--;
				}
				break;
			}
			case (3):
				exit = 1;//�����ϼ��˵�
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//������棬��������
				system("cls");
				menu1_1_2();
				break;
			case(5):
				cerr << "���������������������" << endl;
				exit = 2;
				break;
			}
			if (exit != 0 || exit2) break;
		}
		if (exit == 1)
		{
			break;
		}
		else if (exit == 2 || x.size() == 0) continue;

		if (x.size() != y.size())
		{
			cerr << "������ż��������" << endl;
			continue;
		}
		double ax = sumx / x.size();
		double ay = sumy / y.size();
		double a1 = 0.0,a2=0.0;
		for (unsigned int i = 0; i < x.size(); i++)
		{
			a1 += (x[i] - ax) * (y[i] - ay);
			a2 += pow((x[i] - ax), 2);
		}
		double a = a1 / a2;
		double b = ay - a * ax;
		cout << "�������  y = " << a << "x^"<<n <<showpos<< b << endl;

		double r1 = 0.0,r2 = 0.0;
		for (unsigned int i = 0; i < y.size(); i++)
		{
			r1 += pow((y[i] - ay), 2);
			r2 += pow((a *x[i] + b)-ay, 2);
		}
		cout << "��϶�  R^2 = " <<r2/r1<< endl;
		cout.unsetf(ios::showpos);

		cout << endl;
		cout << ">>>����������n���,�ÿո�ֿ�����ʽ���£��س���ʼ���㡣" << endl;
		cout << ">>>�����㼯(3,2),(4 1) ���� 3 2 4 1" << endl;;
	}
}