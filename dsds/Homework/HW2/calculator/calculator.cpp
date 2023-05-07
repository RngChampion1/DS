#include<iostream>
#include"../../../Stack/Stack.h"
#include <string>
#include <string.h>
//#include<cctype>
#define N_OPTR 9 //���������
using namespace std;

typedef enum { ADD, SUB, MUI, DIV, POW, FAC, L_P, R_P, EOE} Operator;//���������

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

float readNumber(char*& S, Stack<float>& opnd) { //�ú������ǲο���CSDN������ԭ���Ѿ���������
	float x = 0.0;
	bool point = false;//�ж��Ƿ�ΪС��
	int i = 0;//��С������λ��
	while (isdigit(*S) || *S == '.') {
		if (*S != '.') {
			if (point == false) 	x = x * 10 + (*(S++) - 48);//*S���ַ����ͣ�����ASCII����Ҫ��ȥ48����ת��Ϊ����
			if (point == true) { x = x * 10 + (*(S++) - 48); i++; }
		}
		else { S++; point = true; }
	}
	int temp = 1;
	for (int j = 0; j < i; j++) temp *= 10;
	x = x / temp;
	opnd.push(x);//ѹ�������ջ
	return x;
}
float fac(int n) { return (2 > n) ? 1 : n * fac(n - 1); }//��Ȼ���Ľ׳�
float calcu(char optr, float opnd) { return fac(opnd); }
float calcu(float opnd1, char op, float opnd2) {
	float result = 1;
	switch (op) //�ж������
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
{//��׺ʽ��ֵ
	Stack<float> opnd;Stack<char> optr;//������ջ�������ջ
	optr.push('\0');//β�ڱ�'/0'Ҳ��Ϊͷ�ڱ�������ջ
	while (!optr.empty()) {//�������ջ�ǿ�֮ǰ�����������ʽ���ַ�
		if (isdigit(*s)) { //��Ϊ����������
			readNumber(s, opnd); //���������� 
		}
		else
			switch (orderBetween(optr.top(), *s)) {//������ջ�������֮�����ȼ��ߵͷֱ���
			case '<'://ջ����������ȼ�����ʱ
				optr.push(*s); s++; break;//�����Ƴ٣���ǰ�������ջ
			case '='://���ȼ����(��ǰ�����Ϊ�����Ż�����β�ڱ�'\0')ʱ
				optr.pop(); s++; break;//�����ţ�������һ���ַ�
			case '>': {//ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop();//ջ���������ջ
				if ( op == '!') {//������һԪ�����
					float pOpnd = opnd.pop(); 
					opnd.push(calcu(op, pOpnd));//ʵʩһԪ����
				}
				else {//������������Ԫ�������
					float pOpnd2 = opnd.pop();//ȡ���������
					float pOpnd1 = opnd.pop();//ȡ��ǰ������
					opnd.push(calcu(pOpnd1, op, pOpnd2));//ʵʩ��Ԫ���㣬�����ջ
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
