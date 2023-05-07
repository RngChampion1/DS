#pragma once
#include"../Queue/queue.h"
#include"../Stack/stack.h"
#define BinNodePosi(T) BinNode<T>*//节点位置
#define stature(p) ((p)? (p)->height:-1)//节点高度（与“空树高度为-1”的约定相统一）
typedef enum{RB_RED,RB_BLACK}RBColor;//节点颜色

template <typename T>struct BinNode {//二叉树节点模板类
	T data;//数值
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;//父节点及左右孩子
	int height;//高度
	int npl;
	RBColor color;
//构造函数
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0) {}
    BinNode(T e,BinNodePosi(T) p =NULL,BinNodePosi(T) lc=NULL, BinNodePosi(T) rc = NULL,int h=0):
		data(e),parent(p),lc(lc),rc(rc),height(h){}
//操作接口
	int size();//统计当前节点后代总数
	BinNodePosi(T) insertAsLC(T const&); //作为左子树插入
	BinNodePosi(T) insertAsRC(T const&); //作为右子树插入
	BinNodePosi(T) succ(); // 当前节点的直接后继
	template<typename VST> void travLevel(VST&); //层次遍历
	template<typename VST> void travPre(VST&);   //先序遍历
	template<typename VST> void travIn(VST&);    //中序遍历
	template<typename VST> void travPost(VST&); //后序遍历
//比较器、判等器
	bool operator < (BinNode const& bn) { return data < bn.data; }
	bool operator > (BinNode const& bn) { return data > bn.data; }
	bool operator == (BinNode const& bn) { return data == bn.data; }
	bool operator != (BinNode const& bn) { return data != bn.data; }

};
//BinNode状态与性质的判断
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))	//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))	//同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

//与BinNode具有特定关系的节点及指针
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)	//兄弟
#define uncle(x) sibling((x)->parent)	//叔叔
#define FromParentTo(x) /*来自父亲的引用*/\
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))




template<typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lc = new BinNode(e, this);
}

template<typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rc = new BinNode(e, this);
}

template <typename T>int BinNode<T>::size() {
	int s = 1;//计入本身
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

template <typename T> template <typename VST> //元素类型、操作器
void BinNode <T>::travPre(VST& visit) //二叉树先序遍历算法统一入口
{
	switch (rand()%2)
	{
	
	case 1: travPre_I2(this, visit); break; //迭代版#2
	default: travPre_R(this, visit); break; //递归版
	}
}


template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}




//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongLeftBrance(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data); //访问当前节点
		S.push(x->rc); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
		x = x->lc; //沿左分支深入一层
	}
}

template <typename T, typename VST> //元素类型、操作器
void travPre_I2(BinNodePosi(T) x, VST& visit)//二叉树先序遍历算法（迭代版#2）
{
	Stack<BinNodePosi(T)> S; //辅助栈
	while (true)
	{
		visitAlongLeftBrance(x, visit, S); //从当前节点出发，逐批访问
		if (S.empty()) break; //直到栈空
		x = S.pop(); //弹出下一批的起点
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST& visit) //二叉树中序遍历算法统一入口
{
	switch (rand() % 4)  
	{
	case 1: travIn_I1(this, visit); break; //迭代版#1
	case 2: travIn_I2(this, visit); break; //迭代版#2
	case 3: travIn_I3(this, visit); break; //迭代版#3
	default: travIn_R(this, visit); break; //递归版
	}
}

template<typename T,typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template <typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongLeftBrance(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S)
{
	while (x) { S.push(x); x = x->lc; } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I1(BinNodePosi(T) x, VST& visit) //二叉树中序遍历算法（迭代版#1）
{
	Stack<BinNodePosi(T)> S; //辅助栈
	while (true)
	{
		goAlongLeftBrance(x, S); //从当前节点出发，逐批入栈
		if (S.empty()) break; //直至所有节点处理完毕
		x = S.pop(); visit(x->data); //弹出栈顶节点并访问之
		x = x->rc; //转向右子树
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I2(BinNodePosi(T) x, VST& visit) //二叉树中序遍历算法（迭代版#2）
{
	Stack<BinNodePosi(T)> S; //辅助栈
	while (true)
	{
		if (x)
		{
			S.push(x); //根节点进栈
			x = x->lc; //深入遍历左子树
		}
		else if (!S.empty())
		{
			x = S.pop(); //尚未访问的最低祖先节点退栈
			visit(x->data); //访问该祖先节点
			x = x->rc; //遍历祖先的右子树
		}
		else
			break; //遍历完成
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I3(BinNodePosi(T) x, VST& visit)//二叉树中序遍历算法（迭代版#3，无需辅助栈）
{
	bool backtrack = false; //前一步是否刚从左子树回溯——省去栈，仅O(1)辅助空间
	while (true)
	{
		if (!backtrack && HasLChild(*x)) //若有左子树且不是刚刚回溯，则
		{
			x = x->lc; //深入遍历左子树
		}
		else //否则——无左子树或刚刚回溯（相当于无左子树）
		{
			visit(x->data); //访问该节点
			if (HasRChild(*x)) //若其右子树非空，则
			{
				x = x->rc; //深入右子树继续遍历
				backtrack = false; //并关闭回溯标志
			}
			else //若右子树空，则
			{
				if (!(x = x->succ())) break; //回溯（含抵达末节点时的退出返回）
				backtrack = true; //并设置回溯标志
			}
		}
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode <T>::travPost(VST& visit)//二叉树后序遍历算法统一入口
{
	switch (rand()%2)  
	{
	case 1: travPost_I(this, visit); break; //迭代版
	default: travPost_R(this, visit); break; //递归版
	}
}

template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) //沿途所遇节点依次入栈
{
	while (BinNodePosi(T) x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
	{
		if (HasLChild(*x)) //尽可能向左
		{
			if (HasRChild(*x)) S.push(x->rc); //若有右孩子，优先入栈
			S.push(x->lc); //然后才转至左孩子
		}
		else //实不得已
		{
			S.push(x->rc); //才向右
		}
	}
	S.pop(); //返回之前，弹出栈顶的空节点
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit) //二叉树的后序遍历（迭代版）
{
	Stack<BinNodePosi(T)> S; //辅助栈
	if (x) S.push(x); //根节点入栈
	while (!S.empty())// x始终为当前节点
	{
		if (S.top() != x->parent) ////若栈顶非x之父（而为右兄）
		{
			gotoHLVFL(S); //则在其右兄子树中找到HLVFL（相当于递归深入）
		}
		x = S.pop(); visit(x->data); //弹出栈顶（即前一节点之后继），并访问之
	}
}


template<typename T,typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit) {
	if (!x) return;
	travPost_R(x->lc, visit);
	travPosr_R(x->rc, visit);
	visit(x->data);
}
