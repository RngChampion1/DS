#include"complex.h"
#include<ctime>
#include<iostream>
#include<cstdlib>
#include"../../Vector/Vector/Vector.h"
#include"../../Vector/Vector/Vector_fun.h"
using namespace std;
int main() {
	Complex A[10];
	cout << "随机生成无序复数向量" << endl;
	for (int j = 0; j < 10; j++) {
		A[j].read_Real(rand() % 20 + 10);
		A[j].read_Imaginary(rand() % 20 + 10);
		A[j].read_modulus();
		A[j].display();
	}//在屏幕上显示随机向量
	cout << endl;
	Vector<Complex> B(A, 10);

	//置乱 
	B.unsort(0, 10);
	cout << endl << "置乱后" << endl;
	for (int i = 0; i < 10; i++)
		B._elem[i].display();//显示置乱后的向量 

	//查找
	cout << endl;
	int local;
	local = B.find(A[3]);
	cout << endl << "原向量组第三个元素置乱后的位置为" << endl << local << endl;

	//插入
	Vector<Complex> C(A, 1);
	C[0].read_Real(rand() % 10);
	C[0].read_Imaginary(rand() % 10);
	B.insert(10, C[0]);
	cout << endl << "在末尾插入一个随机向量" << endl;
	for (int i = 0; i < 11; i++)
		B._elem[i].display();
	cout << endl;

	//删除
	cout << endl << "删除最后一个向量" << endl;
	B.remove(10);
	for (int i = 0; i < 10; i++)
		B._elem[i].display();
	cout << endl;

	//唯一化
	Vector<Complex> D(A, 1);
	D[0].read_Real(4);
	D[0].read_Imaginary(6);
	int k = rand() % 8 + 2;
	for (int i = 0; i < k; i++)
		B.insert(k, D[0]);
	cout << endl << "唯一化前：" << endl;
	for (int i = 0; i < 10 + k; i++)
		B._elem[i].display();
	int x = B.deduplicate();
	cout << endl << "重复元素个数: " << x << endl;
	cout << endl << "唯一化后：" << endl;
	
	for (int i = 0; i < (10 + k - x); i++)
		B._elem[i].display();


	const int N = 10000;
	Complex E[N];
	cout << endl<<endl;
	cout << "生成随机无序向量" << endl;
	for (int i = 0; i < N; i++) {
		E[i].read_Real(rand() % 20 + 10);
		E[i].read_Imaginary(rand() % 20 + 10);
		E[i].read_modulus();
	}
	cout << endl;

	//冒泡排序 
	Vector<Complex> F(E, N);
	clock_t start_t1, end_t1;
	start_t1 = clock();
	F.bubbleSort(0, N);
	end_t1 = clock();
	double total_t1 = (double)(end_t1 - start_t1);
	cout << "乱序起泡排序时间" << total_t1 << "ms" << endl;

	//归并排序
	Vector<Complex> G(E, N);
	clock_t start_t2, end_t2;
	start_t2 = clock();
	G.mergeSort(0, N);
	end_t2 = clock();
	double total_t2 = (double)(end_t2 - start_t2);
	cout << "乱序归并排序时间" << total_t2 << "ms" << endl;

	//冒泡排序
	clock_t start_t3, end_t3;
	start_t3 = clock();
	F.bubbleSort(0, N);
	end_t3 = clock();
	double total_t3 = (double)(end_t3 - start_t3);
	cout << "顺序起泡排序时间" << total_t3 << "ms" << endl;

	//归并排序
	clock_t start_t4, end_t4;
	start_t4 = clock();
	G.mergeSort(0, N);
	end_t4 = clock();
	double total_t4 = (double)(end_t4 - start_t4);
	cout << "顺序归并排序时间" << total_t4 << "ms" << endl;

	F.bubbleSort(-1, 0, N);//倒序
	//冒泡排序
	clock_t start_t5, end_t5;
	start_t5 = clock();
	F.bubbleSort(0, N);
	end_t5 = clock();
	double total_t5 = (double)(end_t5 - start_t5);
	cout << "倒序起泡排序时间" << total_t5 << "ms" << endl;

	G.bubbleSort(-1, 0, N);//倒序
	//归并排序
	clock_t start_t6, end_t6;
	start_t6 = clock();
	G.mergeSort(0, N);
	end_t6 = clock();
	double total_t6 = (double)(end_t6 - start_t6);
	cout << "倒序归并排序时间" << total_t6 << "ms" << endl;

	
	
	
	Complex H[10];
	cout << "生成无序随机向量";
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
	cout << "排序后" << endl;
	for (int i = 0; i < 10; i++)
		I._elem[i].display();
	cout << endl;

	//区间查找 
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
	cout << "个数为：" << sum << endl;
	for (int i = 0; i < sum; i++)
		I._elem[i].display();















}
