#include"complex.h"
#include<ctime>
#include<iostream>
#include<cstdlib>
#include"../../Vector/Vector/Vector.h"
#include"../../Vector/Vector/Vector_fun.h"
using namespace std;
int main() {
	Complex A[10];
	cout << "�����������������" << endl;
	for (int j = 0; j < 10; j++) {
		A[j].read_Real(rand() % 20 + 10);
		A[j].read_Imaginary(rand() % 20 + 10);
		A[j].read_modulus();
		A[j].display();
	}//����Ļ����ʾ�������
	cout << endl;
	Vector<Complex> B(A, 10);

	//���� 
	B.unsort(0, 10);
	cout << endl << "���Һ�" << endl;
	for (int i = 0; i < 10; i++)
		B._elem[i].display();//��ʾ���Һ������ 

	//����
	cout << endl;
	int local;
	local = B.find(A[3]);
	cout << endl << "ԭ�����������Ԫ�����Һ��λ��Ϊ" << endl << local << endl;

	//����
	Vector<Complex> C(A, 1);
	C[0].read_Real(rand() % 10);
	C[0].read_Imaginary(rand() % 10);
	B.insert(10, C[0]);
	cout << endl << "��ĩβ����һ���������" << endl;
	for (int i = 0; i < 11; i++)
		B._elem[i].display();
	cout << endl;

	//ɾ��
	cout << endl << "ɾ�����һ������" << endl;
	B.remove(10);
	for (int i = 0; i < 10; i++)
		B._elem[i].display();
	cout << endl;

	//Ψһ��
	Vector<Complex> D(A, 1);
	D[0].read_Real(4);
	D[0].read_Imaginary(6);
	int k = rand() % 8 + 2;
	for (int i = 0; i < k; i++)
		B.insert(k, D[0]);
	cout << endl << "Ψһ��ǰ��" << endl;
	for (int i = 0; i < 10 + k; i++)
		B._elem[i].display();
	int x = B.deduplicate();
	cout << endl << "�ظ�Ԫ�ظ���: " << x << endl;
	cout << endl << "Ψһ����" << endl;
	
	for (int i = 0; i < (10 + k - x); i++)
		B._elem[i].display();


	const int N = 10000;
	Complex E[N];
	cout << endl<<endl;
	cout << "���������������" << endl;
	for (int i = 0; i < N; i++) {
		E[i].read_Real(rand() % 20 + 10);
		E[i].read_Imaginary(rand() % 20 + 10);
		E[i].read_modulus();
	}
	cout << endl;

	//ð������ 
	Vector<Complex> F(E, N);
	clock_t start_t1, end_t1;
	start_t1 = clock();
	F.bubbleSort(0, N);
	end_t1 = clock();
	double total_t1 = (double)(end_t1 - start_t1);
	cout << "������������ʱ��" << total_t1 << "ms" << endl;

	//�鲢����
	Vector<Complex> G(E, N);
	clock_t start_t2, end_t2;
	start_t2 = clock();
	G.mergeSort(0, N);
	end_t2 = clock();
	double total_t2 = (double)(end_t2 - start_t2);
	cout << "����鲢����ʱ��" << total_t2 << "ms" << endl;

	//ð������
	clock_t start_t3, end_t3;
	start_t3 = clock();
	F.bubbleSort(0, N);
	end_t3 = clock();
	double total_t3 = (double)(end_t3 - start_t3);
	cout << "˳����������ʱ��" << total_t3 << "ms" << endl;

	//�鲢����
	clock_t start_t4, end_t4;
	start_t4 = clock();
	G.mergeSort(0, N);
	end_t4 = clock();
	double total_t4 = (double)(end_t4 - start_t4);
	cout << "˳��鲢����ʱ��" << total_t4 << "ms" << endl;

	F.bubbleSort(-1, 0, N);//����
	//ð������
	clock_t start_t5, end_t5;
	start_t5 = clock();
	F.bubbleSort(0, N);
	end_t5 = clock();
	double total_t5 = (double)(end_t5 - start_t5);
	cout << "������������ʱ��" << total_t5 << "ms" << endl;

	G.bubbleSort(-1, 0, N);//����
	//�鲢����
	clock_t start_t6, end_t6;
	start_t6 = clock();
	G.mergeSort(0, N);
	end_t6 = clock();
	double total_t6 = (double)(end_t6 - start_t6);
	cout << "����鲢����ʱ��" << total_t6 << "ms" << endl;

	
	
	
	Complex H[10];
	cout << "���������������";
	for (int i = 0; i < 10; i++) {
		H[i].read_Real(rand() % 20 + 10);
		H[i].read_Imaginary(rand() % 20 + 10);
		H[i].read_modulus();
	}
	cout << endl;
	Vector<Complex> I(H, 10);
	for (int i = 0; i < 10; i++) {
		I._elem[i].display();
	}
	cout << endl;
	I.mergeSort(0, 10);
	cout << "�����" << endl;
	for (int i = 0; i < 10; i++)
		I._elem[i].display();
	cout << endl;

	//������� 
	double J[10];
	for (int i = 0; i < 10; i++) {
		J[i] = I._elem[i].display2();
	}
	Vector<Complex> K(H, 10);      
	for (int i = 0; i < 10; i++) {
		K[i].read_Real(J[i]);
		K[i].read_Imaginary(0);
		K[i].read_modulus();
	}
	int sum = K.Find(10, 30, 0, 10);
	cout << "����Ϊ��" << sum << endl;
	for (int i = 0; i < sum; i++)
		I._elem[i].display();















}
