#include"header.h"
#include"matrix.h"
int STATE = 12;//默认模式
int PRECI = 99999999999999;//转换为科学计数法的大小
string ans = "0";
int RAD = 1;//1弧度制，2角度
int HOB = 1;//1十进制,2八进制，3二进制，4十六进制
int CIR = 0;

vector<Matrix> mat;

vector<string> STO;