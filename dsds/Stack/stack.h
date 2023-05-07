#pragma once
#include <iostream>
#include"../Vector/Vector.h"
#include"../Vector/Vector_fun.h" //以向量为基类，派生出栈模板类
using namespace std;
template <typename T> class Stack : public Vector<T> { //将向量的首/末端作为栈底/顶
public: //size()、empty()以及其它开放接口，均可直接沿用
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); } //入栈：等效于将新元素作为向量的末元素插入
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } //出栈：等效于删除向量的末元素
	T& top() { return (*this)[Vector<T>::size() - 1]; } //取顶：直接返回向量的末元素
};