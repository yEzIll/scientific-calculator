#include"header.h"
void enter_instruction()
{
	ifstream fin("instruction.txt", ios::in);
	if (!fin) cerr << "˵���ļ���ʧ" << endl;
	else
	{
		stringstream buffer;
		buffer << fin.rdbuf();
		string str(buffer.str());
		cout << str<<endl;
		cout << ">>>���������" << endl;
	}
	if (cin.peek())
	{
		cin.ignore(255, '\n');
		system("cls");
	}
}