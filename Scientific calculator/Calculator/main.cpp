#include"statistical.h"
#include"basis.h"
#include"setting.h"
#define FILE_BUFFER_LENGTH 30000
extern int STATE;//默认模式
extern int PRECI;//转换为科学计数法的大小
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
	int change = 1;//判断是否输出menu
	while (1)
	{
		menu(change);
		change = 1;//是否打印菜单
		Calculate cal;
		change = cal.run();
		if (change==2) //进入功能模块G
		{
			enter_function();
		}
		else if (change == 3)//进入设置T
		{
			enter_setting();
		}
		else if (change == 4)//进入说明R
		{
			enter_instruction();
		}
		else if (change == 5)//进入存储H
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
		cout << "|||>-----*-----*-----科学计算器*-----*-----*-----<|||\n";
		cout << "|||> *************** 触键功能 ****************** <|||\n";
		cout << "|||> Q ：退出程序               W ：重置屏幕     <|||\n";
		cout << "|||> T ：设置                   R ：使用说明     <|||\n";
		cout << "|||> G : 功能模块               H : 存储         <|||\n";
		cout << "|||===============================================|||\n";
	}
	cout << ">>>输入字母，或直接计算" << endl;
	cout << ">>>";
}

