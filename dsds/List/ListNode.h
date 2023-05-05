#pragma once
#include<iostream>
using namespace std;
typedef int Rank;//��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T> struct ListNode {//�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
//��Ա
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;//��ֵ��ǰ�������
//���캯��
	ListNode(){}
	ListNode(T e,ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		:data (e) ,pred (p),succ(s){}//Ĭ�Ϲ�����
//�����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);//������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsSucc(T const& e);//������ǰ�ڵ�֮������½ڵ�
};

template <typename T>//��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);//�����½ڵ�
	pred->succ = x; pred = x;//������������
	return x;//�����½ڵ��λ��
}

template <typename T>//��e������ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this, succ);//�����½ڵ�
	succ->pred = x; succ = x;//������������
	return x;//�����½ڵ��λ��
}

