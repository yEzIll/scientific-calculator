#include"statistical.h"
int menu1_1(bool change);
void Statistical::run() //2-数据统计运行函数
{
	bool exit = false;
	bool change = true;//判断是否要再次输出menu(),其他情况
	while (true)
	{
		int choice = menu1_1(change);
		change = true;
		switch (choice) {
		case (1)://数据统计-方差与平均值.
			cin.ignore(255, '\n');
			system("cls");
			var_ave();
			break;
		case (2)://线性拟合
			cin.ignore(255, '\n');
			system("cls");
			linear();
			break;
		case (5):
			cin.ignore(255,'\n');
			system("cls");
			exit = true;
			break;
		case(6):
			cin.ignore(); change = false; break;
		default:
			cout << "输入错误，请重新输入" << endl;
			change = false;
			cin.clear();
			cin.ignore(255,'\n');
			break;
		} // end switch
		if (exit == true) break;
		cout << ">>>";
	}
}
int menu1_1(bool change) {
	int choice;
	if (change) {
		cout << " ********* 功能模块 ********* " << endl;
		cout << "(1) 数据统计-方差与平均值. " << endl;
		cout << "(2) 回归拟合." << endl;
		cout << "(Q) 返回上级菜单. " << endl << endl;
		cout << ">>>输入数字进入功能或Q返回" << endl;
	}
	if (cin.peek() == 'Q') return 5;
	else if (cin.peek() == '\n') return 6;
	cin >> choice;
	return choice;
}