#include"matrix.h"

//using namespace std;
extern vector<Matrix> mat;
Matrix::Matrix(int x, int y)
{
	mx = x; my = y;
	el = new double* [mx];
	for (int i = 0; i < mx; i++)
	{
		el[i] = new double[my];
		for (int j = 0; j < my; j++)
		{
			el[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
}
Matrix Matrix::operator-(const Matrix &a)
{
	Matrix c(mx, my);
	for (int i = 0; i < a.mx; i++)
		for (int j = 0; j < a.my; j++)
			c.el[i][j] = el[i][j] - a.el[i][j];
	return c;
}
Matrix Matrix::operator*(const Matrix &a)
{
	int exit = 0;
	Matrix c(mx, a.my);
	for (int i = 0; i < c.mx; i++)
	{
		for (int j = 0; j < c.my; j++)
		{
			for (int k = 0; k < my; k++)
			{
				c.el[i][j] += el[i][k] * a.el[k][j];
			}
		}
	}
	return c;
}
Matrix Matrix::operator+(const Matrix& a)
{
	Matrix c(mx, my);
	for (int i = 0; i < a.mx; i++)
		for (int j = 0; j < a.my; j++)
			c.el[i][j] = el[i][j] + a.el[i][j];
	return c;
}
Matrix op_mat(Matrix a);
Matrix Matrix::operator/(const Matrix& a)
{
	int exit = 0;
	Matrix c(mx, a.my);
	Matrix b(mx, a.my);
	b = op_mat(a);
	if (b.mx == 0) return b;
	for (int i = 0; i < c.mx; i++)
	{
		for (int j = 0; j < c.my; j++)
		{
			for (int k = 0; k < my; k++)
			{
				c.el[i][j] += el[i][k] * b.el[k][j];
			}
		}
	}
	return c;
}
const Matrix& Matrix::operator=(const Matrix& a)
{
	if (mx != a.mx || my != a.my)
	{
		mx = a.mx;
		my = a.my;

		delete[]el;
		el = new double* [mx];
		for (int j = 0; j < mx; j++)
			el[j] = new double[my];
	}
	for (int i = 0; i < mx; i++)
		for (int j = 0; j < my; j++)
		{
			el[i][j] = a.el[i][j];
		}
	return a;
}
ostream& operator<<(ostream& output, const Matrix& a)
{
	if (a.mx == 0 || a.my == 0) output << "| |";
	else for (int i = 0; i < a.mx; i++)
	{
		output << "|";
		for (int j = 0; j < a.my; j++)
		{
			output << setw(3) << setiosflags(ios::right) << a.el[i][j];
			if (j != a.my - 1) output << " ";
		}
		output << "|";
		if (i != a.mx - 1) output << endl;
	}

	return output;
};

string stor_mat(const double a)
{
	ostringstream out;
	out << a;
	string b = out.str();
	while (b.size() > 17 && b[b.size() - 1] != '.')
	{
		b.erase(b.end() - 1);
		if (b.size() == 18 && isdigit(b[b.size() - 1]) && b[b.size() - 1] - '0' > 4)
		{
			b[16]++;
		}
	}
	string::iterator i = b.end() - 1;
	for (; (*i == '0' || *i == '.') && (i != b.begin()); i--)
	{
		if (*i != '.') b.erase(i);
		else {
			b.erase(i);
			break;
		}
	}
	return b;
}
int str_int(string x);//默认模式
bool isnum(string x); 
double str_dou(string x);
bool tiny(double x);

void sto_mat()
{
	fstream bin;
	bin.open("matrix.txt", ios::out);
	if (!bin)
	{
		cerr << "矩阵文件读取失败，开始重置文件" << endl;
	}
	bin << mat.size() << ' ';
	for (int i = 0; i < mat.size(); i++)
	{
		int x = mat[i].mx; int y = mat[i].mx;
		bin << x << ' ' << y << ' ';
		for (int k = 0; k < x; k++)
		{
			for (int l = 0; l < y; l++)
			{
				bin << mat[i].el[k][l];
				if (k == x - 1 && l == y - 1) bin << endl;
				else bin << ' ';
			}
		}

	}
	bin.close();
}
void menu_mat()
{
	cout << "********************矩阵求解******************" << endl;
	cout << "||输入Q离开并保存操作" << endl;
	cout << "||C 创建矩阵；  D 删除矩阵；" << endl;
	cout << "||S 化简矩阵；  U 展开已有矩阵；" << endl;
	cout << "||O 矩阵求逆；  P 计算矩阵；" << endl;
	cout << "||T 倒置矩阵                " << endl;
	cout << "||使用+-*/进行运算" << endl;
	cout << "===============================================" << endl;
	cout << ">>>如对已有矩阵2和3相加，输入M2+M3；" << endl;
}
void sim_mat(Matrix& t)
{
	int ladder = 0; bool con = false;
	vector<int>::iterator k;

	for (int i = 0, c = 0; i < t.mx - 1 && c < t.my; i = i + 1 - ladder, c++)
	{
		con = false;	ladder = 0;

		for (int k = i; k < t.mx && t.el[k][c] == 0;)
		{
			if (t.el[k + 1][c] == 0)
			{
				if (k + 2 < t.mx) { k++; }
				else
				{
					ladder++;
					con = true;
					break;
				}
			}
			else
			{
				for (int j = 0; j < t.my; j++)
				{
					double temp = t.el[k + 1][j];
					t.el[k + 1][j] = t.el[i][j];
					t.el[i][j] = -1 * temp;//将第i行与非0行元素互换
				}
			}
		}
		if (con) continue;

		for (int u = i; u < t.mx - 1; u++)
		{
			double a = t.el[u + 1][c] / t.el[i][c];
			for (int j = 0; j < t.my; j++)
			{
				t.el[u + 1][j] -= t.el[i][j] * a;
			}
		}
	}
}
void t_mat(Matrix& t)
{
	for(int i=0;i<t.mx;i++)
		for (int j = 0; j < i; j++)
		{
			double temp = t.el[i][j];
			t.el[i][j] = t.el[j][i];
			t.el[j][i] = temp;
		}
}
double pri_mat(string str) {
	if (str == "(" || str == "#") return 0;
	else if (str == "+" || str == "-") return 1;
	else if (str == "*" || str == "/") return 2;
	else if (str == "_" || str == "^" || str == "M") return 3;//负号
}

void op_sim_mat(Matrix& t)
{
	int ladder = 0; bool con = false;
	vector<int>::iterator k;

	for (int i = 0, c = 0; i < t.mx - 1 && c < t.my / 2 - 1; i = i + 1 - ladder, c++)
	{
		con = false;	ladder = 0;

		for (int k = i; k < t.mx && t.el[k][c] == 0;)
		{
			if (t.el[k + 1][c] == 0)
			{
				if (k + 2 < t.mx) { k++; }
				else
				{
					ladder++;
					con = true;
					break;
				}
			}
			else
			{
				for (int j = 0; j < t.my; j++)
				{
					double temp = t.el[k + 1][j];
					t.el[k + 1][j] = t.el[i][j];
					t.el[i][j] = -1 * temp;//将第i行与非0行元素互换
				}
			}
		}
		if (con) continue;

		for (int u = i; u < t.mx - 1; u++)
		{
			double a = t.el[u + 1][c] / t.el[i][c];
			for (int j = 0; j < t.my; j++)
			{
				t.el[u + 1][j] -= t.el[i][j] * a;
			}
		}
	}
}
void op_sim_mat2(Matrix& t)
{
	vector<int>::iterator k;

	for (int i = t.mx - 1, c = t.my / 2 - 1; i > 0 && c > 0; i--, c--)
	{

		for (int u = i; u > 0; u--)
		{
			double a = t.el[u - 1][c] / t.el[i][c];
			for (int j = t.my; j >= i; j--)
			{
				t.el[u - 1][j] -= t.el[i][j] * a;
			}
		}
	}
}
Matrix op_mat(Matrix a)
{
	if (a.mx!=a.my)
	{
		cerr << "该矩阵无法求逆" << endl;
		return Matrix(0, 0);
	}

	Matrix tmp(a.mx, a.my * 2);
	for (int i = 0; i < a.mx; i++)
	{
		for (int j = 0; j < a.my; j++)
		{
			tmp.el[i][j] = a.el[i][j];
		}
		for (int j = a.my; j < tmp.my; j++)
		{
			if (j - a.my == i) tmp.el[i][j] = 1;
			else tmp.el[i][j] = 0;
		}
	}
	op_sim_mat(tmp);

	if (tmp.el[a.mx - 1][a.my - 1] == 0)
	{
		cerr << "该矩阵无法求逆" <<endl;
		return Matrix(0, 0);
	}

	op_sim_mat2(tmp);
	for (int i = 0; i < tmp.mx; i++)
	{
		double k = tmp.el[i][i];
		for (int j = 0; j < tmp.my; j++)
		{
			tmp.el[i][j] /= k;
		}
	}

	Matrix tmp2(a.mx, a.my);
	for (int i = 0; i < a.mx; i++)
	{
		for (int j = 0; j < a.my; j++)
		{
			if (tiny(tmp.el[i][j + a.my])) tmp2.el[i][j] = 0;
			else tmp2.el[i][j] = tmp.el[i][j + a.my];
		}
	}
	return tmp2;
}

int cal_mat() {
	vector<string>c1;//存储栈
	vector<string>c2;//临时栈
	vector<Matrix>m;
	c2.push_back("#");
	int last = 0;//0和1意味着减号变负号
	string sym = "+*/^";

	while (true)
	{
		if (isdigit(cin.peek()))
		{
			double x; cin >> x;
			c1.push_back(stor_mat(x));
			last = 2;
		}
		else if (sym.find((char)cin.peek()) != string::npos)//+*/^
		{
			string y;
			cin >> setw(1) >> y;
			while (pri_mat(c2.back()) >= pri_mat(y))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back(y);
			last = 1;
		}
		else if (cin.peek() == '-')
		{
			cin.ignore(); string y;
			if (last == 1 || last == 0)y = "_";
			else y = "-";
			while (pri_mat(c2.back()) > pri_mat(y))
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			c2.push_back(y);
			last = 1;
		}
		else if (cin.peek() == 163) {
			string x;
			cin >> setw(2) >> x;
			if (x == "（")
			{
				c2.push_back("(");
				cin.ignore();
				last = 1;
			}
			else if (x == "）")
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
				cin.ignore();
				last = 2;
			}
			else
			{
				cin.ignore(255, '\n');
				cerr << "错误，请输入正确表达式" << endl;
				return 0;
			}
		}
		else if (cin.peek() == '(')
		{
			c2.push_back("(");
			cin.ignore();
			last = 1;
		}
		else if (cin.peek() == ')')
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
			cin.ignore();
			last = 2;
		}
		else if (cin.peek() == ' ')
		{
			cin.ignore();
		}
		else if (cin.peek() == 'M')
		{
			cin.ignore(); string y;
			if (isdigit(cin.peek()))
			{
				int t; cin >> t;
				if (t >= mat.size())
				{
					cerr << ">>>编号" << t << "为空" << endl;
					cin.ignore(255, '\n');
					return 0;
				}
				y = stor_mat(t);
			}
			else
			{
				cerr << "错误，请输入正确表达式" << endl;
				cin.ignore(255, '\n');
				return 0;
			}
			string x = "M" + y;
			c1.push_back(x);
			last = 2;
		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
			for (int i = c2.size(); i > 1; i--)
			{
				c1.push_back(c2.back());
				c2.pop_back();
			}
			break;//开始运算
		}
		else if (cin.peek() == 'Q')//退出程序
		{
			cin.ignore(255, '\n');
			return 1;
		}
		else if (cin.peek() == 'W')//清空数据，重新输入
		{
			cin.ignore(255, '\n');
			return 2;
		}
		else
		{
			cin.ignore(255, '\n');
			cerr << "错误，请输入正确表达式" << endl;
			return 0;
		}
	}

	for (unsigned __int64 k = 0; k < c1.size(); k++)
	{
		double num; string num2;
		if (c1[k] == "_") {
			if (k < 1) {
				cerr << "错误，请输入正确表达式" << endl;
				return 0;
			}
			if (isnum(c1[k - 1]))
			{
				num = -1 * str_dou(c1[k - 1]);
				c1.insert(c1.begin() + k - 1, stor_mat(num));
				c1.erase(c1.begin() + k, c1.begin() + k + 2);
			}
			else if (c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm')
			{
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];
				Matrix c(a2.mx, a2.my);
				c = a2;

				for (int j = 0; j < c.my; j++)
					c.el[c.mx - 1][j] *= -1;

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			k = 0;
		}
		else if (c1[k] == "+")
		{
			if (k < 2)
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			if (isnum(c1[k - 2]) && isnum(c1[k - 1]))
			{
				num = str_dou(c1[k - 2]) + str_dou(c1[k - 1]);
				c1.insert(c1.begin() + k - 2, stor_mat(num));
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && (c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm'))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);

				Matrix a1 = (c1[k - 2][0] == 'M') ? mat[u1] : m[u1];
				Matrix a2 = (c1[k - 1][0] == 'M') ? mat[u2] : m[u2];


				if (a1.mx != a2.mx || a1.my != a2.my)
				{
					cerr << "无法相加" << endl;
					return 0;
				}

				Matrix c(a1.mx, a1.my);
				c = a1 + a2;
				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else
			{
				cerr << "无法相加" << endl;
				return 0;
			}
			k = 0;
		}
		else if (c1[k] == "-")
		{
			if (k < 2)
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			if (isnum(c1[k - 2]) && isnum(c1[k - 1]))
			{
				num = str_dou(c1[k - 2]) + str_dou(c1[k - 1]);
				c1.insert(c1.begin() + k - 2, stor_mat(num));
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && (c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm'))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);

				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];

				if (a1.mx != a2.mx || a1.my != a2.my)
				{
					cerr << "无法相减" << endl;
					return 0;
				}

				Matrix c(a1.mx, a1.my);
				c = a1 - a2;
				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else
			{
				cerr << "无法相减" << endl;
				return 0;
			}
			k = 0;
		}
		else if (c1[k] == "*")
		{
			if (k < 2)
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			if (isnum(c1[k - 2]) && isnum(c1[k - 1]))
			{
				num = str_dou(c1[k - 2]) * str_dou(c1[k - 1]);
				c1.insert(c1.begin() + k - 2, stor_mat(num));
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && isnum(c1[k - 1]))
			{
				string t1 = c1[k - 2].substr(1);//截取1到尾
				int u1 = str_int(t1);
				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];
				Matrix c(a1.mx, a1.my);
				c = a1;

				double tmp = str_dou(c1[k - 1]);
				for (int j = 0; j < c.my; j++)
					c.el[c.mx - 1][j] *= tmp;

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm') && isnum(c1[k - 2]))
			{
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];
				Matrix c(a2.mx, a2.my);
				c = a2;

				double tmp = str_dou(c1[k - 2]);
				for (int j = 0; j < c.my; j++)
					c.el[c.mx - 1][j] *= tmp;

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && (c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm'))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);

				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];

				if (a1.my != a2.mx)
				{
					cerr << "矩阵无法相乘" << endl;
					return 0;
				}

				Matrix c(a1.mx, a1.my);
				c = a1 * a2;
				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			k = 0;
		}
		else if (c1[k] == "/")
		{
			if (k < 2)
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			if (isnum(c1[k - 2]) && isnum(c1[k - 1]))
			{
				num = str_dou(c1[k - 2]) / str_dou(c1[k - 1]);
				c1.insert(c1.begin() + k - 2, stor_mat(num));
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && isnum(c1[k - 1]))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];
				Matrix c(a1.mx, a1.my);
				c = a1;
				
				double tmp = str_dou(c1[k - 1]);
				for (int j = 0; j < c.my; j++)
					c.el[c.mx - 1][j] /= tmp;

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm') && isnum(c1[k - 2]))
			{
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];
				Matrix c(a2.mx, a2.my);
				c = op_mat(a2);
				if (c.mx == 0)
				{
					cerr << "所计算矩阵无法作为分母" << endl;
					return 0;
				}

				double tmp = str_dou(c1[k - 2]);
				for (int j = 0; j < c.my; j++)
					c.el[c.mx - 1][j] *= tmp;

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && (c1[k - 1][0] == 'M' || c1[k - 1][0] == 'm'))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				string t2 = c1[k - 1].substr(1);
				int u2 = str_int(t2);

				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];
				Matrix a2 = c1[k - 1][0] == 'M' ? mat[u2] : m[u2];

				if (a1.my != a2.mx)
				{
					cerr << "矩阵无法相除" << endl;
					return 0;
				}

				Matrix c(a1.mx, a1.my);
				c = a1 / a2;

				if (c.mx == 0)
				{
					return 0;
				}

				m.push_back(c);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			k = 0;
		}
		else if (c1[k] == "^")
		{
			if (k < 2)
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			if (isnum(c1[k - 2]) && isnum(c1[k - 1]))
			{
				num = pow(str_dou(c1[k - 2]), str_dou(c1[k - 1]));
				c1.insert(c1.begin() + k - 2, stor_mat(num));
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
				k = 0;
			}
			else if ((c1[k - 2][0] == 'M' || c1[k - 2][0] == 'm') && isnum(c1[k - 1]))
			{
				string t1 = c1[k - 2].substr(1);
				int u1 = str_int(t1);
				Matrix a1 = c1[k - 2][0] == 'M' ? mat[u1] : m[u1];

				Matrix b(0, 0);
				b = a1;

				double tmp = str_int(c1[k - 1]);
				for (int j = 1; j < tmp; j++)
					b = a1 * b;

				m.push_back(b);
				string p = "m" + stor_mat(m.size() - 1);
				c1.insert(c1.begin() + k - 2, p);
				c1.erase(c1.begin() + k - 1, c1.begin() + k + 2);
			}
			else
			{
				cerr << "错误，请检查输入格式" << endl;
				return 0;
			}
			k = 0;
		}
	}

	if (c1[0][0] == 'm')
	{
		string t1 = c1[0].substr(1);
		int u1 = str_int(t1);
		cout << m[u1] << endl;

		int tm_x;
		while (true)
		{
			cout << ">>>请输入数字进行存储或Q取消" << endl << ">>>";
			if (isdigit(cin.peek()))
			{
				cin >> tm_x;
				if (tm_x >= mat.size())
				{
					for (size_t i = mat.size(); i < tm_x; i++)
					{
						Matrix k(0, 0);
						mat.push_back(k);
					}
					mat.push_back(m[u1]);
				}
				else
				{
					mat[tm_x] = m[u1];
				}
				cin.ignore(255, '\n');
				cin.sync();
				sto_mat();
				cout << "存储成功,矩阵编号：" << tm_x << endl;
				return 0;
			}
			else if (cin.peek() == 'Q')
			{
				cin.ignore(255, '\n');
				cin.sync();
				sto_mat();
				cout << "取消存储"<< endl;
				return 0;
			}
			cin.ignore(255, '\n');
			cin.sync();
		}
	}
	else if (c1[0][0] == 'M')
	{
		string t1 = c1[0].substr(1);
		int u1 = str_int(t1);
		cout << mat[u1] << endl;

		int tm_x;
		while (true)
		{
			cout << ">>>请输入数字进行存储或Q取消" << endl << ">>>";
			if (isdigit(cin.peek()))
			{
				cin >> tm_x;
				if (tm_x >= mat.size())
				{
					for (int i = mat.size(); i < tm_x; i++)
					{
						Matrix k(0, 0);
						mat.push_back(k);
					}
					mat.push_back(mat[u1]);
				}
				else
				{
					mat[tm_x] = mat[u1];
				}
				cin.ignore(255, '\n');
				cin.sync();
				sto_mat();
				cout << "存储成功,矩阵编号：" << tm_x << endl;
				return 0;
			}
			else if (cin.peek() == 'Q')
			{
				cin.ignore(255, '\n');
				cin.sync();
				cout << "取消存储" << endl;
				return 0;
			}
			cin.ignore(255, '\n');
		}
	}
	else cout << c1[0] << endl;
	sto_mat();
	return 0;
}
int get_mat(Matrix& a)
{
	int mx = a.mx; int my = a.my;
	cout << "请依次输入 " << mx << " 组值，每组 " << my << " 个数" << endl;
	bool contin = false;

	for (int i = 0; i < mx; i++)
	{
		for (int j = 0; j < my; j++)
		{
			if (cin.peek() == 'Q')
			{
				return 1;
			}
			else if (cin.peek() == ' ')
			{
				cin.ignore();
				j--;
			}
			else if(cin.peek() == '\n')
			{
				cin.ignore();
				j--;
				cout << ">>>";
			}
			else if (isdigit(cin.peek())) cin >> a.el[i][j];
			else if (cin.peek() == '-')
			{
				cin.ignore();
				if (isdigit(cin.peek()))
				{
					cin >> a.el[i][j];
					a.el[i][j] *= -1;
				}
				else
				{
					cin.ignore(255, '\n');
					cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
					i = 0;
					break;
				}
			}
			else
			{
				cin.ignore(255, '\n');
				cerr << "错误，请重新输入正确数字或使用Q离开" << endl;
				i = 0;
				break;
			}
		}
	}
	cin.ignore(255, '\n');
}

int matrix_run()
{
	menu_mat();
	mat.erase(mat.begin(), mat.end());//存储新建矩阵
	fstream bin;
	bin.open("matrix.txt", ios::in | ios::out);
	if (!bin)
	{
		cerr << "矩阵文件读取失败，开始重置文件" << endl;
		bin.close();
		bin.open("matrix.txt", ios::out);
		bin.close();
	}
	else
	{
		int size = 0;
		bin >> size;
		while (size--)
		{
			int x = 0; int y = 0;
			bin >> x >> y;
			Matrix a(x, y);
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < y; j++)
				{
					bin >> a.el[i][j];
				}
			}
			mat.push_back(a);
		}
	}
	bin.close();

	while (true)
	{

		int exit = 0;
		cout << ">>>";
		int n;
		if (cin.peek() == 'Q')
		{
			system("cls");
			cin.ignore(255, '\n');
			sto_mat();
			cin.sync();
			return 1;
		}
		else if (cin.peek() == 'W')
		{
			system("cls");
			cin.ignore(255, '\n');
			menu_mat();
			continue;

		}
		else if (cin.peek() == '\n')
		{
			cin.ignore();
			continue;
		}
		else if (isdigit(cin.peek()) || cin.peek() == 'M' || cin.peek() == '-'
			|| cin.peek() == '(' || cin.peek() == 163)
		{
			int excal = cal_mat();
			if (excal == 1)//Q
			{
				system("cls");
				cin.ignore(255, '\n');
				return 1;
			}
			else if (excal == 2)//W
			{
				system("cls");
				cin.ignore(255, '\n');
				menu_mat();
				continue;
			}
		}
		else if (cin.peek() == 'O')
		{
			int mat_x;
			cout << ">>>请输入数字化对某矩阵求逆或Q取消" << endl;
			while (true)
			{
				if (isdigit(cin.peek()))
				{
					cin >> mat_x;
					if (mat_x >= mat.size() || mat[mat_x].mx == 0 || mat[mat_x].my == 0)
					{
						cout << ">>>该编号矩阵为空" << endl;
					}
					else
					{
						Matrix tmp(mat[mat_x].mx, mat[mat_x].my);
						tmp = op_mat(mat[mat_x]);
						if (tmp.mx == 0) break;
						cout << tmp << endl;
						mat[mat_x] = tmp;
					}
					break;
				}
				else if (cin.peek() == 'Q') break;
				else cin.ignore();
			}
			cin.ignore(255, '\n');
			cin.sync();
			sto_mat();
		}
		else if (cin.peek() == 'C')
		{
			system("cls");
			cin.ignore(255, '\n');

			cout << "输入矩阵的高和宽" << endl;
			cout << ">>>";
			int x = 0, y = 0;
			while (true)
			{
				if (isdigit(cin.peek()))
				{
					cin >> x; break;
				}
				else if (cin.peek() == 'Q')
				{
					cin.ignore(255, '\n');
					exit = 1;
					break;
				}
				else if (cin.peek() == ' ')
				{
					cin.ignore();
					continue;
				}
				else if (cin.peek() == '\n')
				{
					cout << ">>>";
					cin.ignore();
					continue;
				}
				else
				{
					cout << "错误，请重新输入" << endl;
					cin.ignore(255, '\n');
					cout << ">>>";
					continue;
				}
			}
			if (exit == 1)
			{
				system("cls");
				menu_mat();
				cout << ">>>退出创建" << endl;
				continue;
			}
			while (true)
			{
				if (exit == 1) break;
				if (isdigit(cin.peek()))
				{
					cin >> y; break;
				}
				else if (cin.peek() == 'Q')
				{
					cin.ignore(255, '\n');
					exit = 1;
					break;
				}
				else if (cin.peek() == ' ')
				{
					cin.ignore();
					continue;
				}
				else if (cin.peek() == '\n')
				{
					cin.ignore();
					cout << ">>>";
					continue;
				}
				else
				{
					cout << "错误，请重新输入" << endl;
					cin.ignore(255, '\n');
					cout << ">>>";
					continue;
				}
			}
			if (exit == 1)
			{
				system("cls");
				menu_mat();
				cout << ">>>退出创建" << endl;
				continue;
			}
			Matrix tmp(x, y);
			exit = get_mat(tmp);
			system("cls");
			cout << ">>>创建成功" << endl;

			cout << tmp << endl;
			int tm_x;
			while (true)
			{
				cout << ">>>请输入数字进行存储或Q取消" << endl << ">>>";
				if (isdigit(cin.peek()))
				{
					cin >> tm_x;
					if (tm_x >= mat.size())
					{
						for (int i = mat.size(); i < tm_x; i++)
						{
							Matrix k(0, 0);
							mat.push_back(k);
						}
						mat.push_back(tmp);
					}
					else
					{
						mat[tm_x] = tmp;
					}
					cin.ignore(255, '\n');
					break;
				}
				else if (cin.peek() == 'Q')
				{
					exit = 1;
					break;
				}
				cin.ignore(255, '\n');
				cin.sync();
			}
			system("cls");
			menu_mat();
			if (exit == 1)
			{
				cin.ignore(255, '\n');
				cin.sync();
				cout << ">>>退出创建" << endl;
				continue;
			}
			cout << "创建成功，矩阵编号：" << tm_x << endl;
			sto_mat();
		}
		else if (cin.peek() == 'U')
		{
			cout << ">>>展开矩阵列表：" << endl;
			vector<Matrix>::iterator k;
			for (k = mat.begin(); k != mat.end(); k++)
			{
				cout << *k << "  矩阵编号：" << distance(mat.begin(), k) << endl;
			}
			cin.ignore(255, '\n');
		}
		else if (cin.peek() == 'S')
		{
			int mat_x;
			cout << ">>>请输入数字化简某矩阵或Q取消" << endl;
			while (true)
			{
				if (isdigit(cin.peek()))
				{
					cin >> mat_x;
					if (mat_x >= mat.size() || mat[mat_x].mx == 0 || mat[mat_x].my == 0)
					{
						cout << ">>>该编号矩阵为空" << endl;
					}
					else
					{
						sim_mat(mat[mat_x]);
						cout << mat[mat_x] << endl;
					}
					break;
				}
				else if (cin.peek() == 'Q') break;
				else cin.ignore();
			}
			cin.ignore(255, '\n');
			cin.sync();
			sto_mat();
		}
		else if (cin.peek() == 'P')
		{
		int mat_x;
		cout << ">>>请输入数字计算某矩阵或Q取消" << endl;
		while (true)
		{
			if (isdigit(cin.peek()))
			{
				cin >> mat_x;
				if (mat_x >= mat.size() || mat[mat_x].mx == 0 || mat[mat_x].my == 0)
				{
					cout << ">>>该编号矩阵为空" << endl;
				}
				else
				{
					Matrix tmp(mat[mat_x].mx, mat[mat_x].my);
					tmp = mat[mat_x];
					if (tmp.mx != tmp.my)
					{
						cerr << "该矩阵无法求值" << endl;
						break;
					}
					sim_mat(tmp); double s = 1.0;
					for (int i = 0; i < tmp.mx; i++)
					{
						s *= tmp.el[i][i];
					}
					if (s == 0)cout << 0 << endl;
					else cout << s << endl;
				}
				break;
			}
			else if (cin.peek() == 'Q') break;
			else cin.ignore();
		}
		cin.ignore(255, '\n');
		cin.sync();
		sto_mat();
		}
		else if (cin.peek() == 'T')
		{
		int mat_x;
		cout << ">>>请输入数字化简某矩阵或Q取消" << endl;
		while (true)
		{
			if (isdigit(cin.peek()))
			{
				cin >> mat_x;
				if (mat_x >= mat.size() || mat[mat_x].mx == 0 || mat[mat_x].my == 0)
				{
					cout << ">>>该编号矩阵为空" << endl;
				}
				else
				{
					if (mat[mat_x].mx != mat[mat_x].my)
					{
						cerr << "该矩阵无法倒置,请重新输入数据" << endl;
						cin.ignore(255, '\n'); cin.clear(); cin.sync();
						continue;
					}
					t_mat(mat[mat_x]);
					cout << mat[mat_x] << endl;
				}
				break;
			}
			else if (cin.peek() == 'Q') break;
			else cin.ignore();
		}
		cin.ignore(255, '\n');
		cin.sync();
		sto_mat();
		}
		else if (cin.peek() == 'D')
		{
			cin.ignore();
			int mat_x;
			cout << ">>>输入数字化删除某矩阵，D清空，Q取消" << endl << ">>>";
			while (true)
			{
				if (isdigit(cin.peek()))
				{
					cin >> mat_x;
					if (mat_x >= mat.size())
					{
						cout << ">>>该编号矩阵为空" << endl;
					}
					else
					{
						mat.erase(mat.begin() + mat_x);
						cout << "删除成功" << endl;
					}
					break;
				}
				else if (cin.peek() == 'D')
				{
					cin.ignore();
					mat.erase(mat.begin(), mat.end());
					cout << "清除成功" << endl;
					break;
				}
				else if (cin.peek() == 'Q') break;
				else cin.ignore();
			}
			cin.ignore(255, '\n');
			cin.sync();
			sto_mat();
		}
		else
		{
			cerr << ">>>错误，请检查输入格式" << endl;
			cin.ignore(255, '\n');
			cin.sync();
			continue;
		}

		if (exit == 1)
		{
			cin.ignore(255, '\n');
			cin.sync();
			system("cls");
			return 1;
		}
		else if (exit == 2)
		{
			cin.ignore(255, '\n');
			cin.sync();
			system("cls");
			menu_mat();
			continue;
		}
	}//

}