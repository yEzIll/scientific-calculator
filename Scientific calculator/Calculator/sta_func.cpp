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
				exit = 1;//返回上级菜单
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//清除界面，重新运算
				system("cls");
				menu1_1_1();
				break;
			default:
				cerr << "数据输入错误，请重新输入" << endl;
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

		cout << "共有：" << x.size() << "个数字" << endl;
		cout << "平均数:" << ave << endl;
		cout << "方差" << var << endl << endl;
	}
}
int var_reception() {
	while (true)
	{
		if (cin.peek() == '\n')
		{
			cin.ignore();
			return 1;//开始运算
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
	cout << ">>>退出界面请输入Q......" << endl;
	cout << ">>>清空数据请输入W......" << endl;
	cout << ">>>请依次输入数据,用空格分开，回车开始运算。" << endl;
	cout << ">>>例：123 456 789" << endl;
}

void menu1_1_2() {
	cout << ">>>退出界面请输入Q......" << endl;
	cout << ">>>清空数据请输入W......" << endl;
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
		cout << "请输入拟合方程系数n,如-1，则对y=ax^-1 +b进行拟合"<<endl;
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
				exit = 1;//返回上级菜单
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//清除界面，重新运算
				system("cls");
				menu1_1_2();
				break;
			case(5):
				cerr << "数据输入错误，请重新输入" << endl;
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
		cout << ">>>请依次输入n组点,用空格分开，格式如下，回车开始运算。" << endl;
		cout << ">>>例：点集(3,2),(4 1) 输入 3 2 4 1" << endl<<">>>";
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
				exit = 1;//返回上级菜单
				cin.ignore(255, '\n');
				system("cls");
				break;
			case (4):
				exit = 2;//清除界面，重新运算
				system("cls");
				menu1_1_2();
				break;
			case(5):
				cerr << "数据输入错误，请重新输入" << endl;
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
			cerr << "请输入偶个数数字" << endl;
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
		cout << "拟合曲线  y = " << a << "x^"<<n <<showpos<< b << endl;

		double r1 = 0.0,r2 = 0.0;
		for (unsigned int i = 0; i < y.size(); i++)
		{
			r1 += pow((y[i] - ay), 2);
			r2 += pow((a *x[i] + b)-ay, 2);
		}
		cout << "拟合度  R^2 = " <<r2/r1<< endl;
		cout.unsetf(ios::showpos);

		cout << endl;
		cout << ">>>请依次输入n组点,用空格分开，格式如下，回车开始运算。" << endl;
		cout << ">>>例：点集(3,2),(4 1) 输入 3 2 4 1" << endl;;
	}
}