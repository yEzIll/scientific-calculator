#include"statistical.h"
int menu1_1(bool change);
void Statistical::run() //2-����ͳ�����к���
{
	bool exit = false;
	bool change = true;//�ж��Ƿ�Ҫ�ٴ����menu(),�������
	while (true)
	{
		int choice = menu1_1(change);
		change = true;
		switch (choice) {
		case (1)://����ͳ��-������ƽ��ֵ.
			cin.ignore(255, '\n');
			system("cls");
			var_ave();
			break;
		case (2)://�������
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
			cout << "�����������������" << endl;
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
		cout << " ********* ����ģ�� ********* " << endl;
		cout << "(1) ����ͳ��-������ƽ��ֵ. " << endl;
		cout << "(2) �ع����." << endl;
		cout << "(Q) �����ϼ��˵�. " << endl << endl;
		cout << ">>>�������ֽ��빦�ܻ�Q����" << endl;
	}
	if (cin.peek() == 'Q') return 5;
	else if (cin.peek() == '\n') return 6;
	cin >> choice;
	return choice;
}