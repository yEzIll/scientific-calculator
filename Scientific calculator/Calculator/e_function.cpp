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
		if (cin.peek() == 'Q')//�����ϼ��˵�
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
			cerr << "����������������ȷ���ֻ�ʹ��Q�뿪" << endl;
		}
		cout << ">>>";
	}
}
bool function(int option)
{
		switch (option) {
		case (1):
		{
			system("cls");//����
			//cin.ignore(255,'\n');

			Statistical a;
			a.run();
			break;
		}
		case (2)://�ⷽ��
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
		case (3)://����任
			system("cls");
			cin.ignore(255, '\n');
			matrix_run();
			break;
		default:
			cout << "������ѡ�� " << endl;
			return false;
		} // end switch
		return true;
}
void menu1(bool change) {
	if (change) {
		cout << " ********* ����ģ�� ********* " << endl;
		cout << "(1) ����ͳ��" << endl;
		cout << "(2) �������" << endl;
		cout << "(3) ����任" << endl;
		cout << ">>>����Q�����ϼ��˵�. " << endl;
		cout << ">>>�������ֽ��빦�ܻ�Q����" << endl;
	}
}



