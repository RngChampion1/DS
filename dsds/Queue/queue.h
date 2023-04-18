#pragma once
#include"../List/List.h"
#include"../List/ListNode.h"
#include<iostream>
using namespace std;
template<typename T> class Queue : public List<T> {//����ģ���ࣨ�̳�Listԭ�нӿڣ�
public:
	void enqueue(T const& e) { insertAsLast(e); }
	T dequeue() { return remove(first()); }
	T& front() { return first()->data; }
};