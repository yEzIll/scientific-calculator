#include"basis.h"
#include"setting.h"
#include"complex.h"

//using namespace std;
extern int STATE;//默认模式
extern int PRECI;//转换为科学计数法的大小
extern int RAD;
extern int HOB;
extern int CIR;
extern string ans;
extern vector<string> STO;
vector<complex> M;

double str_dou(string x);
int str_int(string x);
void str_char(char(*a)[20], string s);
string stor(const double a, const int n);
string com_str(const complex& a, int P);
complex str_com(string a);
string com_str_ans(const complex& a);

string _2_10(string, int);
string _10_2(string, int);
string _8_10(string, int);
string _10_8(string, int);
string _16_10(string, int);
string _10_16(string, int);
bool isnum(string x);

int Calculate::run()
{
	const int P = (STATE < 11) ? STATE : 8;
	int last_choice = 0;
	M.erase(M.begin(), M.end());
	while (true)
	{
		int exit1 = 0;
		int choice = b_reception();
		if (choice == 2
			&& (last_choice == 2
				|| last_choice == 6 || last_choice == 4
				|| (last_choice >= 12 && last_choice <= 15))
			)
		{
			if (cin.peek() == '-') choice = 6;//负号
			else if (cin.peek() == '+') {
				cin.ignore(); continue;
			}
			else
			{
				cerr << "错误，情输入正确表达式" << endl;
				cin.ignore(255, '\n');
				return 0;//不变菜单
			}
		}
		else if (choice == 2 && last_choice == 0)
		{
			if (CIR != 0)
			{
				if (ans[0] == 'M')
				{
					complex tmp = str_com(ans);
					c1.push_back("M" + stor(M.size(), 0));
					M.push_back(tmp);
				}
				else c1.push_back(ans);
			}
			else
			{
				if (cin.peek() == '-') choice = 6;//负号
				else if (cin.peek() == '+') {
					cin.ignore(); continue;
				}
				else
				{
					cerr << "错误，情输入正确表达式" << endl;
					cin.ignore(255, '\n');
					return 0;//不变菜单
				}
			}
		}
		else if ((choice == 18 || choice == 19) && last_choice == 1)
		{
			while (pri(c2.back()) >= pri("*"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("*");
		}

		switch (choice) {
		case (1)://数字
		{
			switch (HOB)
			{
			case(1):
			{
				double x; cin >> x;
				if (cin.peek() == 'i')
				{
					cin.ignore();
					complex tmp(0,x);
					c1.push_back("M" + stor(M.size(), 0));
					M.push_back(tmp);
				}
				else c1.push_back(stor(x, P));
				break;
			}
			case(2):
			{
				double x; cin >> x;
				string bin = stor(x, P);
				for (int i = 0; i < bin.size(); i++)
				{
					if ((bin[i] - '0' < 0 || bin[i] - '0' > 1) && bin[i] != '.')
					{
						cerr << "二进制数格式错误" << endl;
						cin.ignore(255, '\n');
						return 0;
					}
				}
				if (cin.peek() == 'i')
				{
					cin.ignore();
					complex tmp(0, str_dou(_2_10(bin,P)));
					c1.push_back("M" + stor(M.size(), 0));
					M.push_back(tmp);
				}
				else c1.push_back(_2_10(bin, P));
				break;
			}
			case(3):
			{
				double x; cin >> x;
				string bin = stor(x, P);
				for (int i = 0; i < bin.size(); i++)
				{
					if ((bin[i] - '0' < 0 || bin[i] - '0' > 7) && bin[i] != '.')
					{
						cerr << "八进制数格式错误" << endl;
						cin.ignore(255, '\n');
						return 0;
					}
				}
				if (cin.peek() == 'i')
				{
					cin.ignore();
					complex tmp(0, str_dou(_8_10(bin, P)));
					c1.push_back("M" + stor(M.size(), 0));
					M.push_back(tmp);
				}
				else c1.push_back(_8_10(bin, P));
				break;
			}
			case(4):
				string x = "";
				while ((cin.peek() >= 'A' && cin.peek() <= 'F') || isdigit(cin.peek()) || cin.peek() == '.')
				{
					string y;
					cin >> setw(1) >> y;
					x += y;
				}
				if (cin.peek() == 'i')
				{
					cin.ignore();
					complex tmp(0, str_dou(_16_10(x, P)));
					c1.push_back("M" + stor(M.size(), 0));
					M.push_back(tmp);
				}
				else c1.push_back(_16_10(x, P));
				break;
			}
		break;
		}
		case(29):
		{
			complex tmp(0, 1);//i
			c1.push_back("M" + stor(M.size(), 0));
			M.push_back(tmp);
			break;
		}
		case(2)://+-*/^
		{
			string y;
			cin >> setw(1) >> y;
			while (pri(c2.back()) >= pri(y))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back(y);
			break;
		}
		case(3)://!
		{

			string y = "!";
			while (pri(c2.back()) >= pri(y))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back(y);
			break;
		}
		case (4):
			c2.push_back("(");
			break;
		case(5)://）
		{
			vector<string>::iterator k1 = find(c2.begin(), c2.end(), "(");
			if (k1 == c2.end()) {
				cerr << "输入格式错误" << endl;
				cin.ignore(255, '\n');
				return 0;//不输出菜单；
			}
			else {
				for (; c2.back() != "(";)
				{
					c1.push_back(c2.back());
					c2.pop_back();
				}
				c2.pop_back();
			}
			break;
		}
		case(6)://负号
		{
			cin.ignore();
			string y = "_";
			while (pri(c2.back()) > pri(y))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back(y);
			break;
		}
		case (7)://'\n'
		{
			for (int i = c2.size(); i > 1; i--)
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			exit1 = 1;
			break;
		}
		case (8)://退出程序Q
		{
			exit(2);
		}
		case (9)://清屏W
			CIR = 0;
			system("cls");
			return 1;//清屏并重新输出菜单
		case (10)://功能模块G
			CIR = 0;
			system("cls");
			return 2;
		case(11)://设置T
			CIR = 0;
			system("cls");
			return 3;
		case(21)://说明
			CIR = 0;
			system("cls");
			return 4;
		case(12)://sin
		{
			while (pri(c2.back()) > pri("S"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("S");
			break;
		}
		case(13)://cos
		{
			while (pri(c2.back()) > pri("C"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("C");
			break;
		}
		case(14)://tan
		{
			while (pri(c2.back()) > pri("T"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("T");
			break;
		}
		case(26):
		{
			while (pri(c2.back()) > pri("AS"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("AS");
			break;
		}
		case(27):
		{
			while (pri(c2.back()) > pri("AC"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("AC");
			break;
		}
		case(28)://atan
		{
			while (pri(c2.back()) > pri("AT"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back("AT");
			break;
		}
		case(15)://根号
		case(16):
		{
			while (pri(c2.back()) > pri("RT"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			if (choice == 15)c2.push_back("RT");//平方根
			else c2.push_back("ROT");//根号
			break;
		}
		case(17)://pi
		{
			if (last_choice == 1 || last_choice == 3 || last_choice == 5)
			{
				c1.push_back("P1");//执行乘法
			}
			else
			{
				c1.push_back("P2");
			}
			break;
		}
		case(18)://ln
		case(19)://log
		{
			while (pri(c2.back()) > pri("LN"))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			if (choice == 18)c2.push_back("LN");
			else c2.push_back("LOG");
			break;
		}
		case(22)://a+数字
		{
			int num; cin >> num;
			if (STO[num - 1][0] == 'M')
			{
				complex tmp = str_com(STO[num-1]);
				c1.push_back("M" + stor(M.size(), 0));
				M.push_back(tmp);
			}
			else c1.push_back(STO[num - 1]);
			break;
		}
		case(23)://ans
		{
			if (ans[0] == 'M')
			{
				complex tmp = str_com(ans);
				c1.push_back("M" + stor(M.size(), 0));
				M.push_back(tmp);
			}
			else c1.push_back(ans);
			break;
		}
		case(24)://存储H
		{
			CIR = 0;
			system("cls");
			return 5;
		}
		case(25):
		{
			c1.push_back(stor(e, P));
			break;
		}
		default://20
			cin.ignore(255, '\n');
			cout << "输入格式错误，请重新输入! " << endl;
			return 0;
		} // end switch
		last_choice = choice;
		if (exit1 != 0) break;
		}
		//开始计算
	cal_cal(c1, P);
	cin.sync();
	return 0;
}
//接收cin
int Calculate::b_reception() 
{
	while (true) {
		if (isdigit(cin.peek()))
		{
			return 1;//数据载入
		}
		else if (sym.find((char)cin.peek()) != string::npos)//+-*/!^
		{
			if (cin.peek() == '!')
			{
				cin.ignore();
				return 3;
			}
			else return 2;
		}
		else if (cin.peek() == '(')
		{
			cin.ignore();
			return 4;
		}
		else if (cin.peek() == ')')
		{
			cin.ignore();
			return 5;
		}
		else if (cin.peek() == 163) {
			string x;
			cin >> setw(2) >> x;
			if (x == "（") return 4;
			else if (x == "）")return 5;
			else if (x == "！") return 3;
			else return 20;
		}
		else if (cin.peek() == ' ') {
			cin.ignore();
		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
			cin.sync();
			return 7;//开始运算
		}
		else if (cin.peek() == 'Q')//退出程序
		{
			cin.ignore(255,'\n');
			return 8;
		}
		else if (cin.peek() == 'W')//清空数据，重新输入
		{
			cin.ignore(255, '\n');
			return 9;
		}
		else if (cin.peek() == 'G')//功能模块
		{
			cin.ignore();
			//cin.ignore(255, '\n');
			return 10;
		}
		else if (cin.peek() == 'T')//设置
		{
			cin.ignore();
			//cin.ignore(255, '\n');
			return 11;
		}
		else if (cin.peek() == 'R')//使用说明
		{
			cin.ignore(255, '\n');
			return 21;
		}
		else if (cin.peek() == 'H')//存储
		{
			if (ans.size() > 19)
			{
				cin.ignore(255, '\n');
				cerr << "数值过大" << endl;
				return 20;
			}
			cin.ignore();
			return 24;
		}
		else if (cin.peek() == 's' || cin.peek() == 'c' || cin.peek() == 't')
		{
			string y; cin >> setw(3) >> y;
			if (y == "sin") return 12;
			else if (y == "cos")return 13;
			else if (y == "tan")return 14;
			else return 20;
		}
		else if (cin.peek() == 'p' || cin.peek() == 'r')
		{
			string y; cin >> setw(2) >> y;
			if (y == "rt") return 15;//根号2
			else if (y == "ro" && cin.peek() == 't')//根号
			{
				cin.ignore();
				return 16;
			}
			else if (y == "pi") return 17;
			else return 20;
		}
		else if (cin.peek() == 'l')
		{
			string y; cin >> setw(2) >> y;
			if (y == "ln")
			{
				return 18;
			}
			else if (y == "lo" && cin.peek() == 'g')
			{
				cin.ignore();
				return 19;
			}
			else return 20;
		}
		else if (cin.peek() == 'a')
		{
			cin.ignore();
			if(isdigit(cin.peek()))
			{
				return 22;
			}
			else {
				string y; cin >> setw(2) >> y;
				if (y == "ns") return 23;
				else
				{
					string z; cin >> setw(1) >> z;
					y = y + z;
					if (y == "sin") return 26;
					else if (y == "cos")return 27;
					else if (y == "tan")return 28;
					return 20;
				}
			}
		}
		else if (cin.peek() == 'i')
		{
			cin.ignore();
			return 29;
		}
		else if (cin.peek() == 'e')
		{
			cin.ignore();
			return 25;
		}
		else
		{
			if (HOB == 4 && cin.peek() >= 'A' && cin.peek() <= 'F')
			{
			return 1;
			}
			if (cin.peek() == -1)
			{
				cin.ignore();
				cin.clear();
			}
			return 20;
		}
	}
}
//计算
void Calculate::cal_cal(vector<string> x,unsigned int P)//计算
{
		bool correct = true;//是否输出结果
		//int havePI = -1;
		for (size_t k = 0; k < x.size(); k++)
		{
			double num; string num2;
			if(x[k]=="_"){
				if (k<1||(!isnum(x[k - 1])&&x[k-1][0]!='M')) 
				{
					correct = false; break;
				}
				else if (x[k - 1][0] == 'M')
				{
					string t1 = x[k - 1].substr(1);
					int u1 = str_int(t1);
					M[u1].real *= -1; M[u1].ima *= -1;
					x.erase(x.begin()+k);
				}
				else
				{
					num = -1 * str_dou(x[k - 1]);
					x.insert(x.begin() + k - 1, stor(num, P));
					x.erase(x.begin() + k, x.begin() + k + 2);
					
				}
				k = 0;
			}
			else if (x[k] == "!")
			{
				if (k < 1 || !isnum(x[k - 1])) {
					//cerr << "错误，请输入正确表达式" << endl;
					correct = false; break;
				}
				else if(	str_dou(x[k - 1]) < 0|| str_dou(x[k - 1])!= str_int(x[k - 1]))
				{
					//cerr << "错误，请使用非负整数阶乘" << endl;
					correct = false;
					break;
				}
				else if (x.size()>k+1&&x[k + 1] == "!") 
				{
					num2 = fac(str_int(x[k - 1]), 2);
					x.erase(x.begin()+k+1);
				}
				else
				{
					num2 = fac(str_int(x[k - 1]), 1);
				}
				x.insert(x.begin() + k - 1, num2);
				x.erase(x.begin() + k, x.begin() + k + 2);
				k = 0;
				if (x.size() == 1)
				{
					cout << x[0] << endl;
					ans = x[0]; char a[20] = "0"; str_char(&a, ans);
					ofstream bin;
					bin.open("setting.txt", ios::in | ios::out | ios::binary);
					bin.seekp(sizeof(int), ios::beg);
					bin.write(reinterpret_cast<const char*>(&a), 20);
					bin.close();
					correct = false; break;
				}
			}
			else if (x[k] == "+")
			{
				if (k < 2)
				{
					correct = false; break;
				}
				else if (x[k - 2][0] == 'M' && x[k - 1][0] == 'M')
				{
					string t1 = x[k - 1].substr(1);
					int u1 = str_int(t1);
					string t2 = x[k - 2].substr(1);
					int u2 = str_int(t2);
					M[u2] =M[u2]+ M[u1];
					x.erase(x.begin() + k - 1, x.begin() + k + 1);
				}
				else if (x[k - 2][0] == 'M' || x[k - 1][0] == 'M')
				{
					string t1; int u1;
					if (x[k - 2][0] == 'M')
					{
						t1 = x[k - 2].substr(1);
						u1 = str_int(t1);
						M[u1].real += str_dou(x[k - 1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 1);
					}
					else
					{
						t1 = x[k - 1].substr(1);
						u1 = str_int(t1);
						M[u1].real += str_dou(x[k - 2]);
						x.insert(x.begin() + k - 2, x[k-1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 2);
					}
					
				}
				else
				{
					num = str_dou(x[k - 2]) + str_dou(x[k - 1]);
					x.insert(x.begin() + k - 2, stor(num, P));
					x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				k = 0;
			}
			else if (x[k] == "-")
			{
				if (k < 2)
				{
					correct = false; break;
				}
				else if (x[k - 2][0] == 'M' && x[k - 1][0] == 'M')
				{
					string t1 = x[k - 1].substr(1);
					int u1 = str_int(t1);
					string t2 = x[k - 2].substr(1);
					int u2 = str_int(t2);
					M[u2] = M[u2] - M[u1];
					x.erase(x.begin() + k - 1, x.begin() + k + 1);
				}
				else if (x[k - 2][0] == 'M' || x[k - 1][0] == 'M')
				{
					string t1; int u1;
					if (x[k - 2][0] == 'M')
					{
						t1 = x[k - 2].substr(1);
						u1 = str_int(t1);
						M[u1].real -= str_dou(x[k - 1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 1);
					}
					else
					{
						t1 = x[k - 1].substr(1);
						u1 = str_int(t1);
						complex temp(str_dou(x[k - 2]), 0);
						M[u1] = temp- M[u1];
						x.insert(x.begin() + k - 2, x[k - 1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 2);
					}

				}
				else
				{
					num = str_dou(x[k - 2]) - str_dou(x[k - 1]);
					x.insert(x.begin() + k - 2, stor(num, P));
					x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				k = 0;
			}
			else if (x[k] == "*")
			{
				if (k < 2)
				{
					correct = false; break;
				}
				else if (x[k - 2][0] == 'M' && x[k - 1][0] == 'M')
				{
					string t1 = x[k - 1].substr(1);
					int u1 = str_int(t1);
					string t2 = x[k - 2].substr(1);
					int u2 = str_int(t2);
					M[u2] = M[u2] *M[u1];
					x.erase(x.begin() + k - 1, x.begin() + k + 1);
				}
				else if (x[k - 2][0] == 'M' || x[k - 1][0] == 'M')
				{
					string t1; int u1;
					if (x[k - 2][0] == 'M')
					{
						t1 = x[k - 2].substr(1);
						u1 = str_int(t1);
						M[u1].real *= str_dou(x[k - 1]);
						M[u1].ima *= str_dou(x[k - 1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 1);
					}
					else
					{
						t1 = x[k - 1].substr(1);
						u1 = str_int(t1);
						M[u1].real *= str_dou(x[k - 2]);
						M[u1].ima *= str_dou(x[k - 2]);
						x.insert(x.begin() + k - 2, x[k - 1]);
						x.erase(x.begin() + k - 1, x.begin() + k + 2);
					}

				}
				else
				{
					num = str_dou(x[k - 2]) * str_dou(x[k - 1]);
					x.insert(x.begin() + k - 2, stor(num, P));
					x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				k = 0;
			}
			else if (x[k] == "/")
			{
			if (k < 2)
			{
				correct = false; break;
			}
			else if (x[k - 2][0] == 'M' && x[k - 1][0] == 'M')
			{
				string t1 = x[k - 1].substr(1);
				int u1 = str_int(t1);
				string t2 = x[k - 2].substr(1);
				int u2 = str_int(t2);
				M[u2] = M[u2] / M[u1];
				x.erase(x.begin() + k - 1, x.begin() + k + 1);
			}
			else if (x[k - 2][0] == 'M' || x[k - 1][0] == 'M')
			{
				string t1; int u1;
				if (x[k - 2][0] == 'M')
				{
					t1 = x[k - 2].substr(1);
					u1 = str_int(t1);
					M[u1].real /= str_dou(x[k - 1]);
					M[u1].ima /= str_dou(x[k - 1]);
					x.erase(x.begin() + k - 1, x.begin() + k + 1);
				}
				else
				{
					t1 = x[k - 1].substr(1);
					u1 = str_int(t1);

					complex tmp(str_dou(x[k - 2]), 0);
					M[u1] = tmp / M[u1];
					x.insert(x.begin() + k - 2, x[k - 1]);
					x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}

			}
			else
			{
				num = str_dou(x[k - 2]) / str_dou(x[k - 1]);
				x.insert(x.begin() + k - 2, stor(num, P));
				x.erase(x.begin() + k - 1, x.begin() + k + 2);
			}
				k = 0;
			}
			else if (x[k] == "^")
			{
				if (k < 2)
				{
					correct = false; break;
				}
				else if (x[k - 2][0] == 'M' &&isnum(x[k - 1]))
				{
					string t1; int u1;
					t1 = x[k - 2].substr(1);
					u1 = str_int(t1);
					complex tmp = M[u1];
					for (int i = 0; i < str_int(x[k - 1])-1; i++)
					{
						M[u1] = M[u1] * tmp;
					}
					x.erase(x.begin() + k - 1, x.begin() + k + 1);
				}
				else if(isnum(x[k - 2])&& isnum(x[k - 1]))
				{
					num = pow(str_dou(x[k - 2]), str_dou(x[k - 1]));
					x.insert(x.begin() + k - 2, stor(num, P));
					x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				else
				{
					correct = false; break;
				}
				k = 0;
			}
			else if (x[k] == "S" || x[k] == "C" || x[k] == "T" )
			{
				if (k < 1 || !isnum(x[k - 1])) 
				{
					correct = false; break;
				}

				if (RAD == 1)
				{
					double n = str_dou(stor(PI, 8));
					num = str_dou(x[k - 1]) - floor(str_dou(x[k - 1]) / (2 * n)) * 2 * n;
				}
				else
				{
					num = str_dou(x[k - 1]) - floor(str_dou(x[k - 1]) /360.0) * 360;
					num = num * PI / 180;
				}

				if (x[k] == "S") 
				{
					if (tiny(sin(num))) num = 0;
					else num = sin(num);
				}
				else if (x[k] == "C")
				{
					if (tiny(cos(num))) num = 0;
					else num = cos(num);
				}
				else if (x[k] == "T")
				{
					if (tiny(tan(num))) num = 0;
					else num =tan(num);
				}
				x.insert(x.begin() + k - 1, stor(num, P));
				x.erase(x.begin() + k, x.begin() + k + 2);
				k = 0;
			}
			else if (x[k] == "AS" || x[k] == "AC" || x[k] == "AT")
			{
				if (k < 1 || !isnum(x[k - 1]))
				{
					correct = false; break;
				}
				num = str_dou(x[k - 1]);
				if (x[k]!="AT"&&(num>1||num<-1))
				{
					correct = false; break;
				}

				if (RAD == 1)
				{
					if (x[k] == "AS")
					{
						num = asin(num);
					}
					else if (x[k] == "AC")
					{
						num = acos(num);
					}
					else if (x[k] == "AT")
					{
						num = atan(num);
					}
				}
				else
				{
					if (x[k] == "AS")
					{
						num = asin(num)*180/PI;
					}
					else if (x[k] == "AC")
					{
						num = acos(num)*180/PI;
					}
					else if (x[k] == "AT")
					{
						num = atan(num)*180/PI;
					}
				}

				x.insert(x.begin() + k - 1, stor(num, P));
				x.erase(x.begin() + k, x.begin() + k + 2);
				k = 0;
			}
			else if (x[k] == "RT") //平方根
			{
				if (!isnum(x[k-1])||str_dou(x[k - 1]) < 0)
				{
					//cerr << "错误，请输入正确表达式" << endl;
					correct = false; break;
				}
				else
				{
					num = pow(str_dou(x[k - 1]),0.5);
					x.insert(x.begin() + k - 1, stor(num, P));
					x.erase(x.begin() + k, x.begin() + k + 2);
				}
				k = 0;
			}
			else if (x[k] == "ROT") //根号
			{
				if (str_dou(x[k - 1]) < 0|| k <2|| !isnum(x[k - 2]))
				{
					correct = false; break;
				}
				else
				{
				num = pow(str_dou(x[k - 1]), 1.0 / str_dou(x[k - 2]));
				x.insert(x.begin() + k - 2, stor(num, P));
				x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				k = 0;
			}
			else if (x[k] == "P1")
			{
				if (isnum(x[k - 1]))
				{
					//if(str_dou(x[k-1]))
					num = str_dou(x[k - 1]) * str_dou(stor(PI, P));
					x.insert(x.begin() + k-1, stor(num,P));
					x.erase(x.begin() + k,x.begin()+k+2);
					//havePI = k - 1;
				}
				else
				{
					correct = false; break;
				}
				k = 0;
			}
			else if (x[k] == "P2")
			{
				x.insert(x.begin() + k, stor(PI, P));
				x.erase(x.begin() + k + 1);
			}
			else if(x[k]=="LN")
			{
				if (!isnum(x[k-1])||str_dou(x[k - 1]) < 0)
				{
					correct = false; break;
				}
				else
				{
				num = log(str_dou(x[k - 1]));
				if (abs(num - (int)(num+0.5)) < pow(0.1, P>=4?P - 2:P)) num = (int)(num+0.5);
				x.insert(x.begin() + k - 1, stor(num, P));
				x.erase(x.begin() + k, x.begin() + k + 2);
				}
				k = 0;
			}
			else if(x[k]=="LOG")
			{
				if (str_dou(x[k - 1]) < 0 || k < 2 || !isnum(x[k - 2]))
				{
				correct = false; break;
				}
				else
				{
				num = log(str_dou(x[k - 1]))/log( str_dou(x[k - 2]));
				x.insert(x.begin() + k - 2, stor(num, P));
				x.erase(x.begin() + k - 1, x.begin() + k + 2);
				}
				k = 0;
			}
		}


		if (x.size() != 1)
		{ 
			cerr << "错误，请输入正确表达式" << endl; 
		}
		else if (correct)
		{ 
			if(x[0][0]=='M')
			{
				int u1 = str_int(x[0].substr(1));
				ans = "M" + com_str_ans(M[u1]); char a[20] = "0"; str_char(&a, ans);
				ofstream bin;
				bin.open("setting.txt", ios::in | ios::out | ios::binary);
				bin.seekp(sizeof(int), ios::beg);
				bin.write(reinterpret_cast<const char*>(&a), 20);
				bin.close();

				if (STATE == 11 || abs(M[u1].real) > PRECI||abs(M[u1].ima)>PRECI)
				{
					complex a=M[u1];
					if (HOB == 1)
					{
						if (a.real != 0 || a.ima == 0) cout << setprecision(P) << scientific<< a.real;
						if (a.ima != 0)
							if (a.ima < 0) {
								cout << setprecision(P) << scientific << a.ima << "i";
							}
							else {
								if (a.real != 0)cout<< "+";
								cout<< setprecision(P) << scientific <<a.ima << "i";
							}
					}
					else if (HOB == 2)
					{
						if (a.real != 0 || a.ima == 0) cout << setprecision(P) << scientific <<str_dou(_10_2(stor(a.real,P),P));
						if (a.ima != 0)
							if (a.ima < 0) {
								cout << setprecision(P) << scientific << str_dou(_10_2(stor(a.ima, P), P)) << "i";
							}
							else {
								if (a.real != 0)cout << "+";
								cout << setprecision(P) << scientific << str_dou(_10_2(stor(a.ima, P), P)) << "i";
							}
					}
					else if (HOB == 3)
					{
						if (a.real != 0 || a.ima == 0) cout << setprecision(P) << scientific << str_dou(_10_8(stor(a.real, P), P));
						if (a.ima != 0)
							if (a.ima < 0) {
								cout << setprecision(P) << scientific << str_dou(_10_8(stor(a.ima, P), P)) << "i";
							}
							else {
								if (a.real != 0)cout << "+";
								cout << setprecision(P) << scientific << str_dou(_10_8(stor(a.ima, P), P)) << "i";
							}
					}
					else
					{
						string ka = _10_16(stor(a.real, P), P);
						if (ka[ka.size() - 1] == '.') ka.erase(ka.end() - 1);
						string kb = _10_16(stor(a.ima, P), P);
						if (kb[kb.size() - 1] == '.') kb.erase(kb.end() - 1);

						if (a.real != 0 || a.ima == 0) cout << ka;
						if (a.ima != 0)
							if (a.ima < 0) {
								cout << kb << "i";
							}
							else {
								if (a.real != 0)cout << "+";
								cout << kb<< "i";
							}
					}
				}
				else if (STATE == 12)
				{
					complex com(M[u1].real,M[u1].ima);
					string k1, k2;
					if (HOB == 1)
					{
						k1 = stor(com.real, P);
						k2 = stor(com.ima, P);
					}
					else if (HOB == 2)
					{
						k1 = _10_2(stor(com.real,P), P);
						k2= _10_2(stor(com.ima, P), P);
					}
					else if (HOB == 3)
					{
						k1 = _10_8(stor(com.real, P), P);
						k2 = _10_8(stor(com.ima, P), P);
					}
					else
					{
						k1 = _10_16(stor(com.real, P), P);
						k2 = _10_16(stor(com.ima, P), P);
					}
					string::iterator i = k1.end() - 1;
					for (; *i == '0' || *i == '.'; i--)
					{
						if (*i != '.') k1.erase(i);
						else {
							k1.erase(i);
							break;
						}
					}
					i = k2.end() - 1;
					for (; *i == '0' || *i == '.'; i--)
					{
						if (*i != '.') k2.erase(i);
						else {
							k2.erase(i);
							break;
						}
					}
					if (com.real != 0 || com.ima == 0) cout << k1;
					if (com.ima != 0)
						if (com.ima < 0) {
							cout << k2 << "i";
						}
						else {
							if (com.real != 0)cout << "+";
							cout << k2 << "i";
						}
				}
				else
				{
					complex a = M[u1];
					string k1, k2;
					if (HOB == 2)
					{
						k1 = _10_2(stor(a.real, P), P);
						k2 = _10_2(stor(a.ima, P), P);
					}
					else if (HOB == 3)
					{
						k1 = _10_8(stor(a.real, P), P);
						k2 = _10_8(stor(a.ima, P), P);
					}
					else
					{
						k1 = _10_16(stor(a.real, P), P);
						k2 = _10_16(stor(a.ima, P), P);
					}
					if (a.real != 0 || a.ima == 0) cout << k1;
					if (a.ima != 0)
						if (a.ima < 0) {
							cout << k2 << "i";
						}
						else {
							if (a.real != 0)cout << "+";
							cout << k2 << "i";
						}
				}
				cout << endl;
			}
			else
			{
				ans = x[0];
				if (x[0].size() < 20)
				{
					char a[20] = "0"; str_char(&a, ans);
					ofstream bin;
					bin.open("setting.txt", ios::in | ios::out | ios::binary);
					bin.seekp(sizeof(int), ios::beg);
					bin.write(reinterpret_cast<const char*>(&a), 20);
					bin.close();
				}
				if (STATE == 11 || abs(str_dou(x[0])) > PRECI)
				{
					double k;
					if (HOB == 1)
					{
						k = str_dou(x[0]);
						cout << setprecision(P) << scientific << k << endl;
					}
					else if (HOB == 2)
					{
						k = str_dou(_10_2(x[0], P));
						cout << setprecision(P) << scientific << k << endl;
					}
					else if (HOB == 3)
					{
						k = str_dou(_10_8(x[0], P));
						cout << setprecision(P) << scientific << k << endl;
					}
					else
					{
						string ka = _10_16(x[0], P);
						if (ka[ka.size() - 1] == '.') ka.erase(ka.end() - 1);
						cout << ka << endl;
					}
				}
				else if (STATE == 12 && x[0] != "0")
				{
					string k;
					if (HOB == 1)
					{
						k = x[0];
						if (abs(str_dou(k) - (int)(str_dou(k) + 0.5)) < 0.0000001)
						{
							k = stor(str_int(k), P);
						}
					}
					else if (HOB == 2)
					{
						k = _10_2(x[0], P);
					}
					else if (HOB == 3)
					{
						k = _10_8(x[0], P);
					}
					else
					{
						k = _10_16(x[0], P);
					}
					string::iterator i = k.end() - 1;
					for (; *i == '0' || *i == '.'; i--)
					{
						if (*i != '.') k.erase(i);
						else {
							k.erase(i);
							break;
						}
					}
					
					cout << k << endl;
				}
				else
				{
					string k;
					if (HOB == 1)
					{
						k = x[0];
					}
					else if (HOB == 2)
					{
						k = _10_2(x[0], P);
					}
					else if (HOB == 3)
					{
						k = _10_8(x[0], P);
					}
					else
					{
						cout << _10_16(x[0], P);
					}
					cout << k << endl;
				}
			}
			CIR++;
		}
}
//构造析构
Calculate::Calculate() {
	c2.push_back("#");
}
Calculate::~Calculate() {
	c1.~vector();
	c2.~vector();
}
//优先级判断
double Calculate::pri(string str) {
	if (str == "(" || str == "#") return 0;
	else if (str == "+" || str == "-") return 1;
	else if (str == "*" || str == "/") return 2;
	else if (str == "_" || str == "S" || str == "C" ||
			str == "T"  || str == "AS" || str == "AC" ||
			str == "AT" || str == "RT"||str=="ROT"  ||
			str == "^"  ||str=="LN"   ||str=="LOG") return 3;//负号
	else if (str == "!")return 4;
}

//阶乘
string Calculate::fac(int x, int u)
{
	string y = "1";
	if (x == 0) return y;
	for (; x > 0; x = x - u)
	{
		int c = 0;
		for (int i = 0; i < y.size(); i++)
		{
			int tmp = (y[i] - '0') * x + c;//依次用y各个位数乘x
			y[i] = tmp % 10 + '0';//不超过当前y，填改数值
			c = tmp / 10;//获取最后不需要进位的数值
		}
		if (c != 0)
		{
			string t = to_string(c);//将c填到后面
			reverse(t.begin(), t.end());
			y += t;
		}
	}
	reverse(y.begin(), y.end());
	return y;
}
