#include"statistical.h"
#include"basis.h"
#include"setting.h"
#define FILE_BUFFER_LENGTH 30000
extern int STATE;//Ĭ��ģʽ
extern int PRECI;//ת��Ϊ��ѧ�������Ĵ�С
extern string ans;
extern vector<string> STO;

using namespace std;

void menu(int change);
void function(int);
void enter_function();
void enter_setting();
void enter_instruction();
void enter_storage();
void set_setting();
void set_storage();

int main() {
	set_setting(); 
	set_storage();
	int change = 1;//�ж��Ƿ����menu
	while (1)
	{
		menu(change);
		change = 1;//�Ƿ��ӡ�˵�
		Calculate cal;
		change = cal.run();
		if (change==2) //���빦��ģ��G
		{
			enter_function();
		}
		else if (change == 3)//��������T
		{
			enter_setting();
		}
		else if (change == 4)//����˵��R
		{
			enter_instruction();
		}
		else if (change == 5)//����洢H
		{
			enter_storage();
		}
	}
	return 0;
}
void menu(int change)
{
	if (change!=0) {
		cout << " ____________________________________________________\n";
		cout << "|||>-----*-----*-----��ѧ������*-----*-----*-----<|||\n";
		cout << "|||> *************** �������� ****************** <|||\n";
		cout << "|||> Q ���˳�����               W ��������Ļ     <|||\n";
		cout << "|||> T ������                   R ��ʹ��˵��     <|||\n";
		cout << "|||> G : ����ģ��               H : �洢         <|||\n";
		cout << "|||===============================================|||\n";
	}
	cout << ">>>������ĸ����ֱ�Ӽ���" << endl;
	cout << ">>>";
}

