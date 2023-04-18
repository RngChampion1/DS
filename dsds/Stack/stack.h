#pragma once
#include <iostream>
#include"../Vector/Vector.h"
#include"../Vector/Vector_fun.h" //������Ϊ���࣬������ջģ����
using namespace std;
template <typename T> class Stack : public Vector<T> { //����������/ĩ����Ϊջ��/��
public: //size()��empty()�Լ��������Žӿڣ�����ֱ������
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); } //��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } //��ջ����Ч��ɾ��������ĩԪ��
	T& top() { return (*this)[Vector<T>::size() - 1]; } //ȡ����ֱ�ӷ���������ĩԪ��
};