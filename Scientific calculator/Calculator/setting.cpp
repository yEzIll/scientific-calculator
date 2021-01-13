#include"header.h"
#include"setting.h"

extern int STATE;//Ĭ��ģʽ
extern int PRECI;//ת��Ϊ��ѧ�������Ĵ�С
extern int RAD;
extern int HOB;

extern string ans;
extern vector<string> STO;

int str_int(string);
void menu2(bool);
void menu2_1();
bool setting(int);
void accuracy();
void change_setting(int);
bool isnum(string);
void str_char(char(*a)[20],string s);
string char_str(char a[20]);
void rad();
void hob();

void enter_setting() {
	bool change = true;
	while (true)
	{
		menu2(change);
		change = true;
		if (cin.peek() == 'Q')//�����ϼ��˵�
		{
			system("cls");
			cin.ignore(255, '\n');
			cin.sync();
			break;
		}
		else if (isdigit(cin.peek()))
		{
			string option = "0";
			cin >> setw(1) >> option;
			change=setting(str_int(option));
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
bool setting(int option)
{
	switch (option) {
	case (1)://��ʾ����
	{
		system("cls");//����
		//cin.ignore();
		accuracy();
		break;
	}
	case (2)://������
		system("cls");
		//cin.ignore();
		rad();
		break;
	case (3)://����
		system("cls");
		//cin.ignore();
		hob();
		break;
	default:
		cout << "������ѡ�� " << endl;
		return false;
	} // end switch
	return true;
}
void menu2(bool change) {
	if (change) {
		cout << " ********* ���� ********* " << endl;
		cout << "(1) ��ʾ����" << endl;
		cout << "(2) ����" << endl;
		cout << "(3) ����" << endl;
		cout << ">>>����Q�����ϼ��˵�. " << endl;
		cout << ">>>�������ֽ��빦�ܻ�Q����" << endl;
	}
}


void menu2_1() {
		cout << " ********* ���� ********* " << endl;
		cout << "(1) 0.0" << endl;
		cout << "(2) 0.00" << endl;
		cout << "(3) 0.000" << endl;
		cout << "(4) 0.0000" << endl;
		cout << "(5) 0.00000" << endl;
		cout << "(6) 0.000000" << endl;
		cout << "(7) 0.0000000" << endl;
		cout << "(8) 0.00000000" << endl;
		cout << "(9) 0.000000000" << endl;
		cout << "(10)0.0000000000" << endl;
		cout << "(11)��ѧ������" << endl;
		cout << "(12)�Զ�" << endl;
		cout << ">>>�������ֽ������ý��빦�ܻ�Q����" << endl;
		cout << ">>>��ǰ״̬��" << STATE << endl;
}
void accuracy() {
	menu2_1();
	while (true)
	{
		if (cin.peek() == 'Q')//�����ϼ��˵�
		{
			system("cls");
			cin.ignore(255, '\n');
			cin.sync();
			break;
		}
		else if (isdigit(cin.peek()))
		{
			unsigned int option;
			cin >>option;
			if (option < 13 && option>0)
			{
				change_setting(option);
			}
			else {
				cerr << ">>>��������ȷ����"<<endl;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
		}
		else
		{
			cin.ignore(255, '\n');
			cerr << "����������������ȷ���ֻ�ʹ��Q�뿪" << endl;
		}
		cout << ">>>";
	}
}
void set_setting()
{
	fstream bin;
	bin.open("setting.txt", ios::in | ios::binary);
	if (!bin)
	{
		cerr << "�����ļ���ȡʧ�ܣ���ʼ�����ļ�" << endl;
		bin.close();

		bin.open("setting.txt", ios::out | ios::binary);
		int state = 12; char a[20] = "0"; int Rad = 1; int Hob = 1;
		bin.write(reinterpret_cast<const char*>(&state), sizeof(int));//���ܽṹֱ������
		bin.write(reinterpret_cast<const char*>(&a), 20);
		bin.write(reinterpret_cast<const char*>(&Rad), sizeof(int));
		bin.write(reinterpret_cast<const char*>(&Hob), sizeof(int));
		bin.close();

		bin.open("setting.txt", ios::in | ios::binary);
	}
    char a[20] = "0";
	bin.read(reinterpret_cast<char*>(&STATE), sizeof(int));
	bin.read(reinterpret_cast<char*>(&a), 20);
	bin.read(reinterpret_cast<char*>(&RAD), sizeof(int));
	bin.read(reinterpret_cast<char*>(&HOB), sizeof(int));
	ans = char_str(a);

	if (STATE < 1 || STATE>12||(!isnum(ans)&&ans[0]!='M')||(RAD!=1&&RAD!=2)||HOB>4||HOB<1)
	{
		bin.close();
		STATE = 12; ans = "0"; RAD = 1; HOB = 1; char a[20] = "0"; str_char(&a, ans);

		cout << "�����ļ���ʽ�����Զ�����" << endl;
		DeleteFile("setting.txt");
		bin.open("setting.txt", ios::out | ios::binary);
		bin.write(reinterpret_cast<const char*>(&STATE), sizeof(int));//���ܽṹֱ������
		bin.write(reinterpret_cast<const char*>(&a), 20);
		bin.write(reinterpret_cast<const char*>(&RAD),sizeof(int));
		bin.write(reinterpret_cast<const char*>(&HOB), sizeof(int));
	}
	bin.close();
}
void change_setting(int option)
{
	fstream bin;
	bin.open("setting.txt", ios::out|ios::binary);
	bin.write(reinterpret_cast<const char*>(&option), sizeof(int));
	bin.close();

	bin.open("setting.txt", ios::in | ios::binary);
	bin.read(reinterpret_cast<char*>(&STATE), sizeof(int));
	cout << "���óɹ�����ǰ״̬��" << STATE << endl;
	bin.close();
}

void rad()
{
	cout << "***�ǶȻ�����***" << endl;
	cout << "1) ����" << endl;
	cout << "2) �Ƕ�" << endl;
	cout << ">>>Q�����ϼ��˵�" << endl;
	cout << "��ǰ״̬��";
	if (RAD == 1) cout << "������";
	else cout << "�Ƕ���";
	cout << endl;		
	cout << ">>>";

	while (true)
	{
		bool exit = false;
		while (true)
		{
			if (cin.peek() == '\n')
			{
				cin.ignore();
				break;//��ʼ����
			}
			else if (cin.peek() == ' ') {
				cin.ignore();
			}
			else if (cin.peek() == '1' || cin.peek() == '2')
			{
				cin >> RAD;
				if (RAD >= 10) RAD /= 10;
				cout << "���ĳɹ�����ǰ��";
				if (RAD == 1) cout << "������";
				else cout << "�Ƕ���";
				cout << endl;
			}
			else if (cin.peek() == 'Q')
			{
				cin.ignore(255,'\n');
				system("cls");
				cin.sync();
				exit = true;
				break;
			}
			else
			{
				cin.ignore(255, '\n');
				cerr << ">>>�����ʽ����" << endl;
			}
			cout << ">>>";
		}
		if (exit) break;

		fstream bin;
		bin.open("setting.txt", ios::in|ios::out | ios::binary);
		bin.seekp(sizeof(int) + 20);
		bin.write(reinterpret_cast<const char*>(&RAD), sizeof(int));
		bin.close();
	}
}

void hob()
{
	cout << "***����***" << endl;
	cout << "1) ʮ���� "<< endl;
	cout << "2) ������" << endl;
	cout << "3) �˽���" << endl;
	cout << "4) ʮ������" << endl;
	cout << ">>>Q�����ϼ��˵�" << endl;
	cout << "��ǰ״̬��"<<HOB;
	cout << endl;
	cout << ">>>";

	while (true)
	{
		bool exit = false;
		while (true)
		{
			if (cin.peek() == '\n')
			{
				cin.ignore();
				break;//��ʼ����
			}
			else if (cin.peek() == ' ') {
				cin.ignore();
			}
			else if (isdigit(cin.peek())&&(cin.peek() >= '1' || cin.peek() <= '4'))
			{
				cin >> HOB;
				cout << "���ĳɹ�����ǰ״̬��"<<HOB;
				cout << endl;
			}
			else if (cin.peek() == 'Q')
			{
				cin.ignore(255, '\n');
				system("cls");
				exit = true;
				break;
			}
			else
			{
				cin.ignore(255, '\n');
				cerr << ">>>�����ʽ����" << endl;
			}
			cout << ">>>";
		}
		if (exit) break;

		fstream bin;
		bin.open("setting.txt", ios::in | ios::out | ios::binary);
		bin.seekp(28);//int+20+int
		bin.write(reinterpret_cast<const char*>(&HOB), sizeof(int));
		bin.close();
	}
}
