#include"statistical.h"
#include"setting.h"
using namespace std;
int equation();
int muti_equation();
bool tiny(double x)
{
	if (abs(x) < 0.0000000001)
		return true;
	else return false;
}
void menu12(bool change)
{
	if (change) {
		cout << " ********* 方程求解 ********* " << endl;
		cout << "(1) 一元多次方程" << endl;
		cout << "(2) 多元一次方程" << endl;
		cout << ">>>输入Q返回上级菜单. " << endl;
		cout << ">>>输入数字进入功能或Q返回" << endl;
	}
	cout << ">>>";
}
int enter_equation()
{
	while (true)
	{
		if (cin.peek() == 'Q')//返回上级菜单
		{
			system("cls");
			cin.ignore(255, '\n');
			return 0;
		}
		else if (cin.peek() == '1')
		{
			system("cls");
			cin.ignore(255, '\n');
			equation();
			break;
		}
		else if (cin.peek() == '2')
		{
			system("cls");
			cin.ignore(255, '\n');
			muti_equation();
			break;
		}
		else
		{
			cin.ignore(255, '\n');
			cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
			cout << ">>>";
		}
	}
}
int have_solution(double** a, int n)
{
	bool solu = false;//无穷解
	for (int i = n - 1; i >= 0; i--)
	{
		if (a[i][0] != 0)
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (a[i][j] != 0) break;
				else if (j == n) return 0;//无解
			}
		}
		else
		{
			for (int j = 1; j < n + 1; j++)
			{
				if (a[n - 1][j] != 0) break;
				else if (j == n) solu = true;//无解,不return,因后续可能无解
			}
		}
		if (solu) return 1;//无穷解
		return 2;//唯一解
	}
}
int equation()
{
	while (true)
	{
		cout << "一元多次方程求解" << endl;
		cout << "Q离开，W清屏" << endl;
		cout << ">>>请输入方程次方n,n>=4时仅提供1解" << endl << ">>>";
		int n;
		if (cin.peek() == 'Q')
		{
			system("cls");
			cin.ignore(255, '\n');
			cin.sync();
			return 1;
		}
		else if (cin.peek() == 'W')
		{
			system("cls");
			cin.ignore(255, '\n');
			cin.sync();
			continue;
		}
		else if (isdigit(cin.peek()))
		{
			cin >> n;
			cin.ignore();
		}
		else
		{
			cerr << ">>>错误，请检查输入格式" << endl;
			cin.ignore(255, '\n');
			continue;
		}

		bool contin = false;
		double* eq = new double[n];
		for (int i = 0; i < n; i++) eq[i] = 0;
		cout << ">>>请依次输入" << n + 1 << "个数，第一个为X^" << n << "系数，第" << n + 1 << "个为常数" << endl;
		cout << ">>>";
		for (int j = 0; j < n + 1; j++)
		{
			if (cin.peek() == 'Q')
			{
				system("cls");
				cin.ignore(255, '\n');
				cin.sync();
				return 1;
			}
			else if (cin.peek() == 'W')
			{
				system("cls");
				cin.ignore(255, '\n');
				cin.sync();
				contin = true;
				break;
			}
			else if (cin.peek() == ' ' || cin.peek() == '\n')
			{
				cin.ignore();
				j--;
			}
			else if (isdigit(cin.peek())) cin >> eq[j];
			else if (cin.peek() == '-')
			{
				cin.ignore();
				if (isdigit(cin.peek()))
				{
					cin >> eq[j];
					eq[j] *= -1;
				}
				else
				{
					cin.ignore(255, '\n');
					cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
					contin = true;
					break;
				}
			}
			else
			{
				cin.ignore(255, '\n');
				cin.sync();
				cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
				contin = true;
				break;
			}
		}
		if (contin) continue;

		bool all0 = true;//判断是否全为0
		for (int j = 0; j < n + 1; j++)
		{
			if (eq[j] != 0 && j != n) all0 = false;
			if (j == n) cout << " = " << eq[j] << endl;
			else if (eq[j] == 0) {}
			else if (j == n - 1 || (j < n && eq[j + 1] <= 0)) cout << eq[j] << "X^" << n - j << " ";
			else cout << eq[j] << "X^" << n - j << " + ";
		}

		if (all0)
		{
			cerr << "无解" << endl;
			cin.ignore(255, '\n');
			continue;
		}

		if (n == 1)
		{
			cout << "X1 = " << eq[1] / eq[0] << endl;
		}
		else if (n == 2)
		{
			if (eq[0] == 0)
			{
				cout << "X1 = " << eq[2] / eq[1] << endl;
				cin.ignore(255, '\n');
				cout << endl;
				continue;
			}

			double jud = eq[1] * eq[1] + 4 * eq[0] * eq[2];
			if (jud < 0)
			{
				cerr << "无解" << endl;
			}
			else
			{
				cout << "X1 = " << (-1 * eq[1] + sqrt(jud)) / (2 * eq[0]) << endl;
				cout << "X2 = " << (-1 * eq[1] - sqrt(jud)) / (2 * eq[0]) << endl;
			}
		}
		else if (n == 3)
		{
			if (eq[0] == 0)
			{
				if (eq[1] == 0)
				{
					cout << "X1 = " << eq[3] / eq[2] << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}

				double jud = eq[2] * eq[2] + 4 * eq[1] * eq[3];
				if (jud < 0)
				{
					cerr << "无解" << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}
				else
				{
					cout << "X1 = " << (-1 * eq[2] + sqrt(jud)) / (2 * eq[1]) << endl;
					cout << "X2 = " << (-1 * eq[2] - sqrt(jud)) / (2 * eq[1]) << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}
			}
			double p = (3 * eq[0] * eq[2] - eq[1] * eq[1]) / (3 * eq[0] * eq[0]);
			double q = (-27 * pow(eq[0], 2) * eq[3] - 9 * eq[0] * eq[1] * eq[2] +
				2 * pow(eq[1], 3)) / (27 * pow(eq[0], 3));
			double jud = q * q / 4 + p * p * p / 27;
			if (jud > 0)
			{
				double m = (-0.5 * q + sqrt(jud) >= 0) ?
					pow(-0.5 * q + sqrt(jud), 1 / 3.0) : -1 * pow(0.5 * q - sqrt(jud), 1 / 3.0);
				double n = (-0.5 * q - sqrt(jud) >= 0) ?
					pow(-0.5 * q - sqrt(jud), 1 / 3.0) : -1 * pow(0.5 * q + sqrt(jud), 1 / 3.0);
				double x1 = m + n - eq[1] / (3 * eq[0]);
				if (tiny(x1)) x1 = 0;
				cout << "X1 = " << x1 << endl;
			}
			else if (jud == 0)
			{
				if (q == 0)
				{
					cout << "X1 = " << 0 << endl;
					continue;
				}
				double m = q < 0 ? pow(-0.5 * q, 1 / 3.0) : -1 * pow(0.5 * q, 1 / 3.0);
				cout << "X1 = " << 2 * m << endl;
				cout << "X2 = " << -1 * m << endl;
				cout << "X3 = " << m << endl;
			}
			else
			{
				double r = sqrt(pow(-1 * p / 3, 3));
				double xi = acos(-0.5 * q / r) / 3.0;
				cout << "X1 = " << 2 * pow(r, 1 / 3.0) * cos(xi) << endl;
				cout << "X2 = " << 2 * pow(r, 1 / 3.0) * cos(xi + 2 * PI / 3) << endl;
				cout << "X3 = " << 2 * pow(r, 1 / 3.0) * cos(xi + 4 * PI / 3) << endl;
			}
		}
		else if (n == 4 && eq[0] == 0)
		{
			if (eq[1] == 0)
			{
				if (eq[2] == 0)
				{
					cout << "X1 = " << eq[4] / eq[3] << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}

				double jud = eq[3] * eq[3] + 4 * eq[2] * eq[4];
				if (jud < 0)
				{
					cerr << "无解" << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}
				else
				{
					cout << "X1 = " << (-1 * eq[3] + sqrt(jud)) / (2 * eq[2]) << endl;
					cout << "X2 = " << (-1 * eq[3] - sqrt(jud)) / (2 * eq[2]) << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}
			}
			double p = (3 * eq[1] * eq[3] - eq[2] * eq[2]) / (3 * eq[1] * eq[1]);
			double q = (-27 * pow(eq[1], 2) * eq[4] - 9 * eq[3] * eq[1] * eq[2] +
				2 * pow(eq[2], 3)) / (27 * pow(eq[1], 3));
			double jud = q * q / 4 + p * p * p / 27;
			if (jud > 0)
			{
				double m = (-0.5 * q + sqrt(jud) >= 0) ?
					pow(-0.5 * q + sqrt(jud), 1 / 3.0) : -1 * pow(0.5 * q - sqrt(jud), 1 / 3.0);
				double n = (-0.5 * q - sqrt(jud) >= 0) ?
					pow(-0.5 * q - sqrt(jud), 1 / 3.0) : -1 * pow(0.5 * q + sqrt(jud), 1 / 3.0);
				cout << "X1 = " << m + n - eq[2] / (3 * eq[1]) << endl;
			}
			else if (jud == 0)
			{
				if (q == 0)
				{
					cout << "X1 = " << 0 << endl;
					cin.ignore(255, '\n');
					cout << endl;
					continue;
				}
				double m = q < 0 ? pow(-0.5 * q, 1 / 3.0) : -1 * pow(0.5 * q, 1 / 3.0);
				cout << "X1 = " << 2 * m << endl;
				cout << "X2 = " << -1 * m << endl;
				cout << "X3 = " << m << endl;
			}
			else
			{
				double r = sqrt(pow(-1 * p / 3, 3));
				double xi = acos(-0.5 * q / r) / 3.0;
				cout << "X1 = " << 2 * pow(r, 1 / 3.0) * cos(xi) << endl;
				cout << "X2 = " << 2 * pow(r, 1 / 3.0) * cos(xi + 2 * PI / 3) << endl;
				cout << "X3 = " << 2 * pow(r, 1 / 3.0) * cos(xi + 4 * PI / 3) << endl;
			}
		}
		else if (n >= 4)
		{
			double con = 0; int last = 0; double p1; double p2;
			double k = 0;
			for (; abs(eq[n] - con) >= 0.00000001;)
			{
				con = 0;
				for (int i = n; i > 0; i--)
				{
					con += pow(k, i) * eq[n - i];
				}
				if (con < eq[n])
				{
					if (last == 2)
					{
						last = 3;
						p1 = k;
						p2 = k + 10;
						k = (p1 + p2) / 2;
					}
					else if (last == 3)
					{
						p1 = k;
						k = (p1 + p2) / 2;
					}
					else
					{
						k = k + 10;
						last = 1;
					}
				}
				else if (con > eq[n])
				{
					if (last == 1)
					{
						last = 3;
						p2 = k; p1 = k - 10;
						k = (p1 + p2) / 2;
					}
					else if (last == 3)
					{
						p2 = k;
						k = (p1 + p2) / 2;
					}
					else
					{
						k = k - 10;
						last = 2;
					}
				}

			}
			cout << "X =" << k;
		}

		cin.ignore(255, '\n');
		cout << endl;
	}

}
int muti_equation()
{
	while (true)
	{
		cout << ">>>多元一次方程求解" << endl;
		cout << ">>>请输入未知量个数n,或Q离开，W返回" << endl;
		cout << ">>>";
		int n;
		if (cin.peek() == 'Q')
		{
			system("cls");
			cin.ignore(255, '\n');
			cin.sync();
			return 1;
		}
		else if (cin.peek() == 'W')
		{
			system("cls");
			cin.ignore(255, '\n');
			continue;
		}
		else if (isdigit(cin.peek()))
		{
			cin >> n;
			cin.ignore();
		}
		else
		{
			cerr << ">>>错误，请检查输入格式" << endl;
			cin.ignore(255, '\n');
			continue;
		}

		bool contin = false;
		cout << ">>>请依次输入" << n << "组未知量系数，每组有" << n + 1 << "个系数" << endl;
		cout << ">>>系数间使用空格分开，第1个为常数，第n个为Xn的系数" << endl;
		double** equ = new double* [n];

		for (int i = 0; i < n; i++) equ[i] = new double[n + (size_t)1];
		for (int i = 0; i < n; i++)
		{
			cout << ">>>";
			for (int j = 0; j < n + 1; j++)
			{
				if (cin.peek() == 'Q')
				{
					system("cls");
					cin.ignore(255, '\n');
					return 1;
				}
				else if (cin.peek() == 'W')
				{
					system("cls");
					cin.ignore(255, '\n');
					contin = true;
					break;
				}
				else if (cin.peek() == ' ' || cin.peek() == '\n')
				{
					cin.ignore();
					j--;
				}
				else if (isdigit(cin.peek())) cin >> equ[i][j];
				else if (cin.peek() == '-')
				{
					cin.ignore();
					if (isdigit(cin.peek()))
					{
						cin >> equ[i][j];
						equ[i][j] *= -1;
					}
					else
					{
						cin.ignore(255, '\n');
						cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
						contin = true;
						break;
					}
				}
				else
				{
					cin.ignore(255, '\n');
					cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
					contin = true;
					break;
				}
			}
			if (contin) break;
		}
		if (contin) continue;

		int ladder = 0; bool con = false;//
		vector<int> inf;//判断哪个数是无限
		vector<int>::iterator k;

			for (int i = 0, c = 1; i < n - 1 && c < n + 1; i = i + 1 - ladder, c++)
			{
				con = false;	ladder = 0;

				for (int k = i; k < n && equ[k][c] == 0;)
				{
					if (equ[k + 1][c] == 0)
					{
						if (k + 2 < n) { k++; }
						else
						{
							inf.push_back(c);
							ladder++;
							con = true;
							break;
						}
					}
					else
					{
						for (int j = 0; j < n + 1; j++)
						{
							double temp = equ[k + 1][j];
							equ[k + 1][j] = equ[i][j];
							equ[i][j] = temp;//将第i行与非0行元素互换
						}
					}
				}
				if (con) continue;

				for (int u = i; u < n - 1; u++)
				{

					double a = equ[u + 1][c] / equ[i][c];
					for (int j = 0; j < n + 1; j++)
					{
						equ[u + 1][j] -= equ[i][j] * a;
					}
				}
			}

		int solution = have_solution(equ, n);

		for (int i = 0; i < n; i++)
		{
			cout << "{" << equ[i][0] << " = ";
			for (int j = 1; j < n; j++)
			{
				if (equ[i][j + 1] < 0)
				{
					cout << equ[i][j];
					if(equ[i][j]!=0)cout<< "X" << j;
					cout<< " ";
				}
				else
				{
					cout << equ[i][j];
					if (equ[i][j] != 0)cout << "X" << j;
					cout<< " +";
				}
			}
			cout << equ[i][n];
			if (equ[i][n] != 0)cout << "X" << n;
			cout<<endl;
		}

		double* x = new double[n];//用于存取结果X1,X2,X3……
		for (int i = 0; i < n; i++) x[i] = 0;


		int freenum = 0;//有多少个自由未知量
		double** fre = new double* [n];
		if (solution == 0) { cout << "无解" << endl; }
		else if (solution == 2)//唯一解
		{
			for (int i = n - 1; i >= 0; i--)
			{
				x[i] = equ[i][0];
				for (int j = i + 2; j < n + 1; j++)
				{
					x[i] -= x[j - 1] * equ[i][j];
				}
				if (equ[i][i + 1] != 0)
				{
					x[i] = x[i] / equ[i][i + 1];
				}
				else
				{
					for (int j = 1; j < n + 1; j++)
					{
						if (equ[i][j] != 0)
						{
							x[j] = x[j] / equ[i][j];
						}
					}
				}
			}
		}
		else//无穷解
		{
			for (int i = n - 1; i >= 0; i--)
			{
				if (equ[i][0] == 0)
				{
					for (int j = 1; j < n + 1; j++)
					{
						if (equ[i][j] != 0) break;
						else if (j == n)
						{
							freenum++;
						}
					}
				}
				else break;
			}

			size_t diff = freenum - inf.size();//补齐自由未知量
			for (int u = 0; u < diff; u++)
			{
				vector<int> pro;//保护不变自由
				for (int i = n - 1 - freenum; i >= 0; i--)
				{
					int sum = 0;
					int tmp = 0;
					for (int j = 1; j < n + 1; j++)
					{
						if (equ[i][j] != 0)
						{
							tmp = j; sum++;
						}
						if (j == n && sum == 1)
						{
							pro.push_back(tmp);
						}
					}
				}
				for (int j = n; j > 0; j--)
				{
					vector<int>::iterator l;
					k = find(inf.begin(), inf.end(), j);
					l = find(pro.begin(), pro.end(), j);
					if (k == inf.end() && l == pro.end())
					{
						inf.push_back(j);
						break;
					}
				}
			}//inf存储完毕

			for (int i = 0; i < n; i++)
			{
				fre[i] = new double[freenum];
				for (int j = 0; j < n; j++)
				{
					fre[i][j] = 0;
				}
			}//令equ[i][0]等于0，再分别令自由变量为1，得到结果X1,X2,X3……

			double** tmp = new double* [n];
			for (int i = 0; i < n; i++)//将自由未知量全部变0，求取特解
			{
				tmp[i] = new double[n + (size_t)1];
				for (int j = 0; j < n + 1; j++)
				{
					k = find(inf.begin(), inf.end(), j);
					if (k != inf.end())
					{
						tmp[i][j] = 0;
					}
					else tmp[i][j] = equ[i][j];
				}
			}

	
			for (int i = n - 1 - freenum; i >= 0; i--)
			{
				int u = 0;
				for (int j = 1; j < n + 1; j++)
				{
					if (tmp[i][j] != 0.0)
					{
						u = j - 1;
						x[u] = tmp[i][0];
						break;
					}
				}
				for (int j = u + 2; j < n + 1; j++)
				{
					x[u] -= x[j - 1] * tmp[i][j];
				}
				x[u] = x[u] / tmp[i][u + 1];
			}//算出x[u]的值,x[0]对应x1
		//得到所有特解

			for (int k = 0; k < inf.size(); k++)
			{
				for (int i = 0; i < n; i++)
				{
					tmp[i][0] = -1 * equ[i][inf[k]];
				}//令tmp[i][0]全部为0

				for (int i = n - 1 - freenum; i >= 0; i--)
				{
					int u = 0;
					for (int j = 1; j < n + 1; j++)
					{
						if (tmp[i][j] != 0)
						{
							u = j - 1;
							fre[u][k] = tmp[i][0];
							break;
						}
					}
					for (int j = u + 2; j < n + 1; j++)
					{
						fre[u][k] -= fre[j-1][k] * tmp[i][j];
					}
					fre[u][k] /= tmp[i][u + 1];
					fre[inf[k]-1][k] = 1.0;
				}//算出x[u]的值,x[0]对应x1
			}
		
		}


		if (solution == 2)
		{
			for (int l = 0; l < n; l++)
			{
				k = find(inf.begin(), inf.end(), l + 1);
				if (k != inf.end()) cout << "X" << l + 1 << "= R" << endl;
				else cout << "X" << l + 1 << "=" << x[l] << endl;
			}
		}
		else if (solution == 1)
		{
			for (int l = n-1; l >= 0; l--)
			{
				cout << "X" << l+1 << " = " << x[l];
				for (int k = 0; k < freenum; k++)
				{
					if (fre[l][k] == 0) continue;
					cout << showpos << fre[l][k] << "k";
					cout.unsetf(ios::showpos);
						cout<<k+1;
				}
				cout << endl;
			}
		}
		cout.flush();
		cin.ignore(255, '\n');
		cout << endl;
	}
}