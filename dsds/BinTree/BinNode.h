#pragma once
#include"../Queue/queue.h"
#include"../Stack/stack.h"
#define BinNodePosi(T) BinNode<T>*//�ڵ�λ��
#define stature(p) ((p)? (p)->height:-1)//�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
typedef enum{RB_RED,RB_BLACK}RBColor;//�ڵ���ɫ

template <typename T>struct BinNode {//�������ڵ�ģ����
	T data;//��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;//���ڵ㼰���Һ���
	int height;//�߶�
	int npl;
	RBColor color;
//���캯��
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0) {}
    BinNode(T e,BinNodePosi(T) p =NULL,BinNodePosi(T) lc=NULL, BinNodePosi(T) rc = NULL,int h=0):
		data(e),parent(p),lc(lc),rc(rc),height(h){}
//�����ӿ�
	int size();//ͳ�Ƶ�ǰ�ڵ�������
	BinNodePosi(T) insertAsLC(T const&); //��Ϊ����������
	BinNodePosi(T) insertAsRC(T const&); //��Ϊ����������
	BinNodePosi(T) succ(); // ��ǰ�ڵ��ֱ�Ӻ��
	template<typename VST> void travLevel(VST&); //��α���
	template<typename VST> void travPre(VST&);   //�������
	template<typename VST> void travIn(VST&);    //�������
	template<typename VST> void travPost(VST&); //�������
//�Ƚ������е���
	bool operator < (BinNode const& bn) { return data < bn.data; }
	bool operator > (BinNode const& bn) { return data > bn.data; }
	bool operator == (BinNode const& bn) { return data == bn.data; }
	bool operator != (BinNode const& bn) { return data != bn.data; }

};
//BinNode״̬�����ʵ��ж�
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))	//����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))	//ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))

//��BinNode�����ض���ϵ�Ľڵ㼰ָ��
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)	//�ֵ�
#define uncle(x) sibling((x)->parent)	//����
#define FromParentTo(x) /*���Ը��׵�����*/\
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))




template<typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lc = new BinNode(e, this);
}

template<typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rc = new BinNode(e, this);
}

template <typename T>int BinNode<T>::size() {
	int s = 1;//���뱾��
	if (lc) s += lc->size();
	if (rc) s += rc->size();
	return s;
}


template <typename T> BinNodePosi(T) BinNode<T>::succ() 
{
	BinNodePosi(T) s = this; 
	if (rc)
	{ 
		s = rc; 
		while (HasLChild(*s)) s = s->lc; 
	}
	else
	{ 
		while (IsRChild(*s)) s = s->parent; 
		s = s->parent; 
	}
	return s;
}

template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST& visit) {
	Queue<BinNodePosi(T)>Q;
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue(); visit(x->data);
		if (HasLChild(*x)) Q.enqueue(x->lc); 
		if (HasRChild(*x)) Q.enqueue(x->rc); 

	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPre(VST& visit) //��������������㷨ͳһ���
{
	switch (rand()%2)
	{
	
	case 1: travPre_I2(this, visit); break; //������#2
	default: travPre_R(this, visit); break; //�ݹ��
	}
}


template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}




//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T, typename VST> //Ԫ�����͡�������
static void visitAlongLeftBrance(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data); //���ʵ�ǰ�ڵ�
		S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
		x = x->lc; //�����֧����һ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi(T) x, VST& visit)//��������������㷨��������#2��
{
	Stack<BinNodePosi(T)> S; //����ջ
	while (true)
	{
		visitAlongLeftBrance(x, visit, S); //�ӵ�ǰ�ڵ��������������
		if (S.empty()) break; //ֱ��ջ��
		x = S.pop(); //������һ�������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit) //��������������㷨ͳһ���
{
	switch (rand() % 4)  
	{
	case 1: travIn_I1(this, visit); break; //������#1
	case 2: travIn_I2(this, visit); break; //������#2
	case 3: travIn_I3(this, visit); break; //������#3
	default: travIn_R(this, visit); break; //�ݹ��
	}
}

template<typename T,typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongLeftBrance(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
	while (x) { S.push(x); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(BinNodePosi(T) x, VST& visit) //��������������㷨��������#1��
{
	Stack<BinNodePosi(T)> S; //����ջ
	while (true)
	{
		goAlongLeftBrance(x, S); //�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break; //ֱ�����нڵ㴦�����
		x = S.pop(); visit(x->data); //����ջ���ڵ㲢����֮
		x = x->rc; //ת��������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2(BinNodePosi(T) x, VST& visit) //��������������㷨��������#2��
{
	Stack<BinNodePosi(T)> S; //����ջ
	while (true)
	{
		if (x)
		{
			S.push(x); //���ڵ��ջ
			x = x->lc; //�������������
		}
		else if (!S.empty())
		{
			x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
			visit(x->data); //���ʸ����Ƚڵ�
			x = x->rc; //�������ȵ�������
		}
		else
			break; //�������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(BinNodePosi(T) x, VST& visit)//��������������㷨��������#3�����踨��ջ��
{
	bool backtrack = false; //ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ�
	while (true)
	{
		if (!backtrack && HasLChild(*x)) //�����������Ҳ��Ǹոջ��ݣ���
		{
			x = x->lc; //�������������
		}
		else //���򡪡�����������ոջ��ݣ��൱������������
		{
			visit(x->data); //���ʸýڵ�
			if (HasRChild(*x)) //�����������ǿգ���
			{
				x = x->rc; //������������������
				backtrack = false; //���رջ��ݱ�־
			}
			else //���������գ���
			{
				if (!(x = x->succ())) break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
				backtrack = true; //�����û��ݱ�־
			}
		}
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPost(VST& visit)//��������������㷨ͳһ���
{
	switch (rand()%2)  
	{
	case 1: travPost_I(this, visit); break; //������
	default: travPost_R(this, visit); break; //�ݹ��
	}
}

template <typename T> //����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) //��;�����ڵ�������ջ
{
	while (BinNodePosi(T) x = S.top()) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
	{
		if (HasLChild(*x)) //����������
		{
			if (HasRChild(*x)) S.push(x->rc); //�����Һ��ӣ�������ջ
			S.push(x->lc); //Ȼ���ת������
		}
		else //ʵ������
		{
			S.push(x->rc); //������
		}
	}
	S.pop(); //����֮ǰ������ջ���Ŀսڵ�
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit) //�������ĺ�������������棩
{
	Stack<BinNodePosi(T)> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ
	while (!S.empty())// xʼ��Ϊ��ǰ�ڵ�
	{
		if (S.top() != x->parent) ////��ջ����x֮������Ϊ���֣�
		{
			gotoHLVFL(S); //�����������������ҵ�HLVFL���൱�ڵݹ����룩
		}
		x = S.pop(); visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮
	}
}


template<typename T,typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travPost_R(x->lc, visit);
	travPosr_R(x->rc, visit);
	visit(x->data);
}
