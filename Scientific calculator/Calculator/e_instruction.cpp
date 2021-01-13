#include"header.h"
void enter_instruction()
{
	ifstream fin("instruction.txt", ios::in);
	if (!fin) cerr << "说明文件丢失" << endl;
	else
	{
		stringstream buffer;
		buffer << fin.rdbuf();
		string str(buffer.str());
		cout << str<<endl;
		cout << ">>>任意键返回" << endl;
	}
	if (cin.peek())
	{
		cin.ignore(255, '\n');
		system("cls");
	}
}