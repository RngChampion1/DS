#pragma once
#include"BinNode.h"
#include<iostream>
template<typename T> class BinTree {
protected:
	int _size; BinNodePosi(T) _root;//��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�������ȵĸ߶�
public:
	BinTree() :_size(0), _root(NULL) {}//���캯��
	~BinTree() { if (0 < _size) remove(_root); }//��������
	int size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�
	BinNodePosi(T) root() const { return _root; } //����
	BinNodePosi(T)  insertAsRoot(T const& e); //������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e��Ϊx�����ӽڵ����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e��Ϊx���Һ��ӽڵ����
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree <T>*& T); //T��Ϊ����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree <T>*& T); //T��Ϊ����������
	int remove(BinNodePosi(T) x); //ɾ����x�ڵ�Ϊ������������������ԭ�ȵĹ�ģ 
	BinTree<T>* secede(BinNodePosi(T) x); //ɾ��������������ת��Ϊ�������� 


	template <typename VST> //������
	void travLevel(VST& visit) //��α���
	{
		if (_root) _root->travLevel(visit);
	}

	template <typename VST> void travPre(VST& visit) //�������
	{
		if (_root) _root->travPre(visit);
	}

	template <typename VST> void travIn(VST& visit) //�������
	{
		if (_root) _root->travIn(visit);
	}

	template <typename VST> void travPost(VST& visit) //�������
	{
		if (_root) _root->travPost(visit);
	}

	bool operator<(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && lt(_root, t._root);
	}
	bool operator<=(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && !(mt(_root, t._root));
	}
	bool operator>(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && mt(_root, t._root);
	}
	bool operator>=(BinTree<T> const& t) //�Ƚ���
    {
		return _root && t._root && !(lt(_root, t._root));
	}
	bool operator==(BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root == t._root);
	}
	bool operator!=(BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root != t._root);
	}

};
 
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x) //���½ڵ�x�߶�
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));//���������������
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //���¸߶�
{
	while (x) { updateHeight(x); x = x->parent; }//��x�����������������ȡ����Ż�
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);//��e�������ڵ����յĶ�����
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;// e����Ϊx������
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T)x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;// e����Ϊx���Һ���
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T)x, BinTree<T>*& S)  // x->lc == NULL
{
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T)x, BinTree<T>*& S)// x->rc == NULL
{
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x)// assert: xΪ�������еĺϷ�λ��
{
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x) // assert: xΪ�������еĺϷ�λ��
{
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} // release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ������

template <typename T> struct Cleaner
{
	static void clean(T x) {} //�൱�ڵݹ��
};

template <typename T> struct Cleaner<T*>
{
	static void clean(T* x)
	{
		if (x) { delete x; } //������а���ָ�룬�ݹ��ͷ�
	}
};

template <typename T> void release(T x) { Cleaner<T>::clean(x); }

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)// assert: xΪ�������еĺϷ�λ��
{
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } 
template <typename T> static bool lt(T& a, T& b) { return a < b; } 
template <typename T> static bool mt(T* a, T* b) { return mt(*a, *b); } 
template <typename T> static bool mt(T& a, T& b) { return a > b; } 
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } 
template <typename T> static bool eq(T& a, T& b) { return a == b; } 

