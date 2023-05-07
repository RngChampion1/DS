#pragma once
#include"../List/List.h"
#include"../List/ListNode.h"
#include<iostream>
using namespace std;
template<typename T> class Queue : public List<T> {//队列模板类（继承List原有接口）
public:
	void enqueue(T const& e) {List<T>::insertAsLast(e); }
	T dequeue() { return List<T>::remove(List<T>::first()); }
	T& front() { return List<T>::first()->data; }
};