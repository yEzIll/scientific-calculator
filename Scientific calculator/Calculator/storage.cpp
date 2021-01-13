#include"header.h"
#include"setting.h"

extern int STATE;//Ĭ��ģʽ
extern int PRECI;//ת��Ϊ��ѧ�������Ĵ�С

extern string ans;
extern vector<string> STO;


using namespace std;
void re_storage();//�����ļ�
void storage(const int);//��ȡ����
bool isnum(string);
void set_storage();//��ȡ����
void de_storage(const int);//ɾ������
void menu6();//�˵�
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
				cerr << "������1��20�������" << endl;
				change = false;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == 'Q')//�����ϼ��˵�
		{
			system("cls");
			cin.ignore(255, '\n');
			break;
		}
		else if (cin.peek() == 'D')//ɾ��ָ����
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
					cerr << "������1��20�������" << endl;
					change = false;
				}
			}
			else 
			{
				cerr << "��������ȷ��ʽ" << endl;
				change = false;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == 'C')//ɾ�������ļ�
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
			cerr << "������������" << endl;
			change = false;
		}
	}
}
void storage(const int num)//��ȡ����
{
	fstream bin;
	bin.open("storage.txt", ios::in|ios::out | ios::binary);
	if (!bin) cerr << "�ļ���ʧ��" << endl;

	bin.seekp(((__int64)num - 1) * 20);
	char a[20] = "0"; str_char(&a, ans);
	bin.write(reinterpret_cast<const char*>(&a), 20);
	STO[num - 1] = ans;
	bin.close();
}
void de_storage(const int num)//ɾ������
{
	fstream bin;
	bin.open("storage.txt", ios::in | ios::out | ios::binary);
	if (!bin) cerr << "�ļ���ʧ��" << endl;

	bin.seekp(((__int64)num - 1) * 20);
	char a[20] = " ";
	bin.write(reinterpret_cast<const char*>(&a), 20);
	STO[num - 1] = "_";
	bin.close();
}
void re_storage()//�����ļ�
{
	STO.erase(STO.begin(),STO.end());
	DeleteFile("storage.txt");

	ofstream bin;
	bin.open("storage.txt", ios::out | ios::binary);
	if (!bin) cerr << "�ļ�����ʧ��" << endl;

	char a[20] = "_";
	for (int i = 0; i < 20; i++) 
	{
		bin.write(reinterpret_cast<const char*>(&a), 20);
		STO.push_back("_");
	}
	bin.close();
}
void set_storage()//��ȡ����
{
	fstream bin;
	bin.open("storage.txt", ios::in | ios::binary);
	if (!bin)
	{
		cerr << "�洢�ļ���ȡʧ��,��ʼ����,�����´�Ӧ��" << endl;
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
			cerr << "�洢�ļ��𻵣���ʼ����" << endl;
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
	cout << ">>>�������ִ�ȡ��ǰֵ��Q�˳���D+����ɾ��ָ����,C���" << endl;
}