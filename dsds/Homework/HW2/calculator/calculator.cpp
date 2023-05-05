#include<iostream>
#include"../../../Stack/Stack.h"
#include <string>
#include <string.h>
//#include<cctype>
#define N_OPTR 9 //运算符总数
using namespace std;

typedef enum { ADD, SUB, MUI, DIV, POW, FAC, L_P, R_P, EOE} Operator;//运算符集合

const char pri[N_OPTR][N_OPTR] = {
	'>','>','<','<','<','<','<','>','>',
	'>','>','<','<','<','<','<','>','>',
	'>','>','>','>','<','<','<','>','>',
	'>','>','>','>','<','<','<','>','>',
	'>','>','>','>','>','<','<','>','>',
	'>','>','>','>','>','>',' ','>','>',
	'<','<','<','<','<','<','<','=',' ',
	' ',' ',' ',' ',' ',' ',' ',' ',' ',
	'<','<','<','<','<','<','<',' ','=',
};

int change(char c) {
	switch (c)
	{
	case '+':return ADD; break;
	case '-':return SUB; break;
	case '*':return MUI; break;
	case '/':return DIV; break;
	case '^':return POW; break;
	case '!':return FAC; break;
	case '(':return L_P; break;
	case ')':return R_P; break;
	case '\0':return EOE; break;
	}
}

float readNumber(char*& S, Stack<float>& opnd) { //该函数我是参考的CSDN，但是原理已经搞明白了
	float x = 0.0;
	bool point = false;//判断是否为小数
	int i = 0;//计小数点后的位数
	while (isdigit(*S) || *S == '.') {
		if (*S != '.') {
			if (point == false) 	x = x * 10 + (*(S++) - 48);//*S是字符类型，根据ASCII表需要减去48才能转化为数字
			if (point == true) { x = x * 10 + (*(S++) - 48); i++; }
		}
		else { S++; point = true; }
	}
	int temp = 1;
	for (int j = 0; j < i; j++) temp *= 10;
	x = x / temp;
	opnd.push(x);//压入操作数栈
	return x;
}
float fac(int n) { return (2 > n) ? 1 : n * fac(n - 1); }//自然数的阶乘
float calcu(char optr, float opnd) { return fac(opnd); }
float calcu(float opnd1, char op, float opnd2) {
	float result = 1;
	switch (op) //判断运算符
	{
	case '+': {result = opnd1 + opnd2; return result; }
	case '-': {result = opnd1 - opnd2; return result; }
	case '*': {result = opnd1 * opnd2; return result; }
	case '/': {result = opnd1 / opnd2; return result; }
	case '^': {for (int i = 0; i < opnd2; i++) result *= opnd1; return result; }
	}//switch
}
char orderBetween(char c1, char c2) {
	return pri[change(c1)][change(c2)];
}

float evaluter(char* s)
{//中缀式求值
	Stack<float> opnd;Stack<char> optr;//运算数栈、运算符栈
	optr.push('\0');//尾哨兵'/0'也作为头哨兵首先入栈
	while (!optr.empty()) {//在运算符栈非空之前，逐个处理表达式中字符
		if (isdigit(*s)) { //若为操作数，则
			readNumber(s, opnd); //则读入操作数 
		}
		else
			switch (orderBetween(optr.top(), *s)) {//视其与栈顶运算符之间优先级高低分别处理
			case '<'://栈顶运算符优先级更低时
				optr.push(*s); s++; break;//计算推迟，当前运算符进栈
			case '='://优先级相等(当前运算符为右括号或者是尾哨兵'\0')时
				optr.pop(); s++; break;//脱括号，接收下一个字符
			case '>': {//栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
				char op = optr.pop();//栈顶运算符出栈
				if ( op == '!') {//若属于一元运算符
					float pOpnd = opnd.pop(); 
					opnd.push(calcu(op, pOpnd));//实施一元运算
				}
				else {//对于其他（二元）运算符
					float pOpnd2 = opnd.pop();//取出后操作数
					float pOpnd1 = opnd.pop();//取出前操作数
					opnd.push(calcu(pOpnd1, op, pOpnd2));//实施二元运算，结果入栈
				}
				break;
			}
			default:exit(-1);
			}
	}
	
	return opnd.pop();
}

int main(int argc, char** argv) {
	char S1[] = "4.1+3!"; cout << "4.1+3!=" << evaluter(S1) << endl;
	char S2[] = "(3.2-1.9)*2"; cout << "(3.2-1.9)*2=" << evaluter(S2) << endl;
	char S3[] = "(5+3)+2^3+4!/2"; cout << "(5+3)+2^3+4!/2=" << evaluter(S3) << endl;


}
