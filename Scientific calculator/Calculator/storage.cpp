#include"header.h"
#include"setting.h"

extern int STATE;//默认模式
extern int PRECI;//转换为科学计数法的大小

extern string ans;
extern vector<string> STO;


using namespace std;
void re_storage();//重置文件
void storage(const int);//存取数据
bool isnum(string);
void set_storage();//获取数据
void de_storage(const int);//删除数据
void menu6();//菜单
void str_char(char(*a)[20], string s);
string char_str(char a[20]);

void enter_storage()
{
	bool change = true;
	while (true)
	{
		if(change) menu6();
		change = true;
		if (isdigit(cin.peek()))
		{
			int num;
			cin >> num;
			if (num > 0 && num < 21)
			{
				system("cls");
				storage(num);
			}
			else
			{
				cerr << "请输入1到20间的数字" << endl;
				change = false;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == 'Q')//返回上级菜单
		{
			system("cls");
			cin.ignore(255, '\n');
			break;
		}
		else if (cin.peek() == 'D')//删除指定项
		{
			cin.ignore();
			if (isdigit(cin.peek()))
			{
				int num;
				cin >> num;
				if (num > 0 && num < 21)
				{
					system("cls");
					de_storage(num);
				}
				else 
				{
					cerr << "请输入1到20间的数字" << endl;
					change = false;
				}
			}
			else 
			{
				cerr << "请输入正确格式" << endl;
				change = false;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == 'C')//删除重置文件
		{
			system("cls");
			cin.ignore(255, '\n');
			re_storage();
		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
			change = false;
		}
		else
		{
			cin.ignore(255, '\n');
			cerr << "错误，请检查输入" << endl;
			change = false;
		}
	}
}
void storage(const int num)//存取数据
{
	fstream bin;
	bin.open("storage.txt", ios::in|ios::out | ios::binary);
	if (!bin) cerr << "文件打开失败" << endl;

	bin.seekp(((__int64)num - 1) * 20);
	char a[20] = "0"; str_char(&a, ans);
	bin.write(reinterpret_cast<const char*>(&a), 20);
	STO[num - 1] = ans;
	bin.close();
}
void de_storage(const int num)//删除数据
{
	fstream bin;
	bin.open("storage.txt", ios::in | ios::out | ios::binary);
	if (!bin) cerr << "文件打开失败" << endl;

	bin.seekp(((__int64)num - 1) * 20);
	char a[20] = " ";
	bin.write(reinterpret_cast<const char*>(&a), 20);
	STO[num - 1] = "_";
	bin.close();
}
void re_storage()//重置文件
{
	STO.erase(STO.begin(),STO.end());
	DeleteFile("storage.txt");

	ofstream bin;
	bin.open("storage.txt", ios::out | ios::binary);
	if (!bin) cerr << "文件创建失败" << endl;

	char a[20] = "_";
	for (int i = 0; i < 20; i++) 
	{
		bin.write(reinterpret_cast<const char*>(&a), 20);
		STO.push_back("_");
	}
	bin.close();
}
void set_storage()//获取数据
{
	fstream bin;
	bin.open("storage.txt", ios::in | ios::binary);
	if (!bin)
	{
		cerr << "存储文件获取失败,开始重置,请重新打开应用" << endl;
		re_storage();
	}

	bin.seekg(0);
	for (int i = 0; i < 20; i++)
	{
		char a[20] = "0";
		bin.read(reinterpret_cast<char*>(&a), 20);
		string ss = char_str(a);
		if (ss == "_" || isnum(ss)||ss[0]=='M') STO.push_back(ss);
		else
		{
			cerr << "存储文件损坏，开始重置" << endl;
			re_storage();
			break;
		}
	}
	bin.close();
}
void menu6()
{
	
	for (int i = 0; i < 20; i++)
	{
		cout<<i+1 << ")" << STO[i] << endl;
	}
	cout << ">>>输入数字存取当前值，Q退出，D+数字删除指定项,C清空" << endl;
}