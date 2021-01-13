#include"statistical.h"
//#include"setting.h"
using namespace std;
int str_int(string);

void menu1(bool change);
bool function(int);

void menu12(bool change);
int enter_equation();
int equation();
int muti_equation();
int have_solution(double** a, int n);

int matrix_run();

void enter_function() {
	bool change = true;
	while (true) 
	{
		menu1(change);
		change = true;
		if (cin.peek() == 'Q')//返回上级菜单
		{
			system("cls");
			cin.ignore(255,'\n');
			cin.sync();
			break;
		}
		else if (isdigit(cin.peek()))
		{
			string option = "0";
			cin >>setw(1)>> option;
			change=function(str_int(option));
		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
			change = false;
		}
		else
		{
			change = false;
			cin.ignore(255, '\n');
			cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
		}
		cout << ">>>";
	}
}
bool function(int option)
{
		switch (option) {
		case (1):
		{
			system("cls");//清屏
			//cin.ignore(255,'\n');

			Statistical a;
			a.run();
			break;
		}
		case (2)://解方程
		{
			system("cls");
			cin.ignore(255,'\n');

			int c2 = 1;
			while (true)
			{
				menu12(c2);
				c2 = enter_equation();
				if (c2 == 0) break;
				//else if(c2)
			}
			break;
		}
		case (3)://矩阵变换
			system("cls");
			cin.ignore(255, '\n');
			matrix_run();
			break;
		default:
			cout << "请重新选择 " << endl;
			return false;
		} // end switch
		return true;
}
void menu1(bool change) {
	if (change) {
		cout << " ********* 功能模块 ********* " << endl;
		cout << "(1) 数据统计" << endl;
		cout << "(2) 方程求解" << endl;
		cout << "(3) 矩阵变换" << endl;
		cout << ">>>输入Q返回上级菜单. " << endl;
		cout << ">>>输入数字进入功能或Q返回" << endl;
	}
}



