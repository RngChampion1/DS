#pragma once
#include "Vector.h"//引用模板类


template<typename T>
inline void Vector<T>::swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}


template <typename T>//元素类型
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {//以数组区间A[lo,hi)为蓝本复制向量
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0; //分配空间，规模清零
	while (lo < hi) //A[lo,hi)内元素的逐一
		_elem[_size++] = A[lo++]; //复制至_elem[0,hi-lo)
}

template<typename T>
void Vector<T>::expand() //向量空间不足时扩容
{
	if (_size < _capacity)
	{
		
		return;//尚未满员时不必扩容 
	}
	if (_capacity < DEFAULT_CAPACITY)
	{
		_capacity = DEFAULT_CAPACITY; //保证不低于原来的容量 
	}
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//容量加倍
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];//复制原向量内容（T为基本类型，或已重载赋值操作符'='）
	}
	delete[]oldElem;//释放原空间 
}

template<typename T>
void Vector<T>::shrink() //装填因子过小时压缩向量所占空间
{
	if (_capacity < DEFAULT_CAPACITY << 1)
	{
		return; //不致收缩到DEFAULT_CAPACITY以下
	}
	if (_size << 2 > _capacity)
	{
		return;//以25%为界
	}
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];//容量减半
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //复制原向量内容
	}
	delete[]oldElem;//释放原空间
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)  
{  //一趟扫描交换
	bool sorted = true; //整体有效标志
	while (++lo < hi)//自左向右，逐一检查各对相邻元素
		if (_elem[lo - 1] > _elem[lo])  //若逆序，则意味着尚未整体有序，并需要通过交换
		{                               //使局部有序
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted;//返回有序标志
}

template<typename T>
bool Vector<T>::bubble(Rank n, Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1] < _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);	//交换两个值
		}
	}
	return sorted;
}

template<typename T>
void Vector<T>::bubbleSort(Rank n, Rank lo, Rank hi)	//冒泡排序
{
	while (!bubble(n, lo, hi--));
}


template<typename T>//向量的起泡元素
void Vector<T>::bubbleSort(Rank lo, Rank hi)//asset:0<=lo<hi<=size
{
	while (!bubble(lo, hi--));
} //逐趟做扫描交换，直至全序

template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi)//在[lo, hi]内找出最大者
{
	Rank max = lo;
	while (++lo < hi)
		if (_elem[lo] >= _elem[max])//取等保证在最大值相同情况下总是取最后一个
		{
			max = lo;
		}
	return max;//返回最大值的秩
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) // 0 <= lo < hi <= size
{
	while (lo < --hi)
	{
		swap(_elem[max(lo, hi)], _elem[hi]); //将[hi]与[lo, hi]中的最大者交换
	}
}

template<typename T>//对各自有序的[lo, mi)和[mi, hi)做归并
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)// lo < mi < hi
{//以mi 为界，各自有序的子向量[lo,mi) [mi, hi)
	T* A = _elem + lo; //合并后的向量A[0,hi-lo) = _elem[lo,hi)
	int lb = mi - lo;
	T* B = new T[lb];//前子向量B[0,lb) = _elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);//复制前子向量,只有前面的有必要复制，有被覆盖的风险
	int lc = hi - mi;
	T* C = _elem + mi;//前子向量C[0,lc) = _elem[mi,hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)// 将B[j]和C[k]中的小者续至A的末尾
	{
		if ((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || C[k] < B[j])) A[i++] = C[k++];
	}
	delete[]B; //释放临时空间B
}// 归并后得到完整的有序向量 [lo,hi)

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return; //单元素区间自然有序
	Rank mi = (lo + hi) / 2; //以中点为界
	mergeSort(lo, mi);
	mergeSort(mi, hi); //前缀、后缀分别排序
	merge(lo, mi, hi); //归并
}

template<typename T>//通过调整元素位置，构造出区间[lo, hi)内的一个轴点
Rank Vector<T>::partition(Rank lo, Rank hi)// DUP版：可优化处理多个关键码雷同的退化情况
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
	T pivot = _elem[lo]; //经以上交换，等效于随机选取候选轴点
	while (lo < hi)//从两端交替扫描，直至相遇
	{
		do hi--;
		while ((lo < hi) && (pivot < _elem[hi])); //向左拓展后缀G
		if (lo < hi)
		{
			_elem[lo] = _elem[hi];//阻挡者归入前缀L
		}
		do lo++;
		while ((lo < hi) && (_elem[lo] < pivot)); //向右拓展前缀L
		if (lo < hi)
		{
			_elem[hi] = _elem[lo]; //阻挡者归入后缀G
		}
	} // assert: quit with lo == hi or hi + 1
	_elem[hi] = pivot; //候选轴点置于前缀、后缀之间，它便名副其实
	return hi; //返回轴点的秩
}


template < typename T> //向量快速排序
 void Vector<T>::quickSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
	   if (hi - lo < 2) return; //单元素区间自然有序，否则...
	    Rank mi = partition(lo, hi); //在[lo, hi)内构造轴点
	   quickSort(lo, mi); quickSort(mi + 1, hi); //前缀、后缀各自递归排序
}

 template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
	     T * A = _elem + lo; Rank n = hi - lo; heapify(A, n); //将待排序区间建成一个完全二叉堆，O(n)
	     while (0 < --n) //反复地摘除最大元并归入已排序的后缀，直至堆空
		    { swap(A[0], A[n]); percolateDown(A, n, 0); } //堆顶与末元素对换，再下滤
 }
 
 template<typename T>
 int  Vector<T>::Find(int min, int max, Rank lo, Rank hi) {
	 int count = 0;
	 for (int i = lo; i < hi; i++) {
		 if (_elem[i] > min * min && _elem[i] < max * max) {
			 _elem[count] = _elem[i];
			 count++;
		 }
	 }
	 return count;
 }

 template<typename T>
 inline int Vector<T>::disordered() const
 {
	 int n = 0;
	 for (int i = 1; i < _size; i++)
	 {
		 if (_elem[i - 1] > _elem[i])
		 {
			 n++;
		 }
	 }
	 return n;//当且仅当n=0时向量有序 
 }

 template<typename T>//在无序向量中顺序查找e：成功则返回最靠后的出现位置，否则返回lo - 1
  Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
 {  //0 <= lo < hi <= _size
	 while ((lo < hi--) && (e != _elem[hi])); //从后向前，顺序查找
	 return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩
 }

  template<typename T>
  inline Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
  {
	  while (lo < hi) { //每步迭代仅需做一次比较判断，有两个分支
		  Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度折半，等效于其数值表示的右移一位）
		  (e < this[mi]) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
	  } //成功查找不能提前终止
	  return lo - 1; //至此，[lo]为大于e的最小者，故[lo-1]即为不大于e的最大者
  }
  template <typename T>
  T& Vector<T>::operator[] (Rank r) //重载下标操作符
  {
	  return _elem[r];
  } // assert: 0 <= r < _size

  template<typename T>
  inline Vector<T>& Vector<T>::operator=(Vector<T> const& V) //重载
  {
	  if (_elem)
	  {
		  delete[]_elem;  //释放原有内容
	  }
	  copyFrom(V._elem, 0, V.size()); //整体复制
	  return *this; //返回当前对象的引用，以便链式赋值
  }
  template <typename T>
  const T& Vector<T>::operator[] (Rank r) const //仅限于做右值
  {
	  return _elem[r];
  } // assert: 0 <= r < _size

  template<typename T>
   T Vector<T>::remove(Rank r)
  {
	  T e = _elem[r]; //备份被删除元素
	  remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
	  return e; //返回被删除元素
  }

  template<typename T>
   int Vector<T>::remove(Rank lo, Rank hi)//删去[lo,hi)
  {
	  if (lo == hi) return 0; //出于效率考虑，单独处理退化情况
	  while (hi < _size) _elem[lo++] = _elem[hi++]; //后缀[hi, _size)顺次前移hi-lo位
	  _size = lo;
	  shrink(); //更新规模，lo=_size之后的内容无需清零；如必要，则缩容
	  return hi - lo; //返回被删除元素的数目
  }
   template<typename T>
    Rank Vector<T>::insert(Rank r, T const& e)
   {
	   expand(); //如必要，先扩容
	   for (Rank i = _size; r < i; i--) //自后向前，后继元素
	   {
		   _elem[i] = _elem[i - 1];//顺次后移一个单元
	   }
	   _elem[r] = e; _size++; //置入新元素并更新容量
	   return r; //返回秩
   }

	template <typename T> void Vector<T>::sort(Rank lo, Rank hi) { //向量区间[lo, hi)排序
		   switch (rand() % 5) {
		       case 1: bubbleSort(lo, hi); break; //起泡排序
		       case 2: selectionSort(lo, hi); break; //选择排序（习题）
		       case 3: mergeSort(lo, hi); break; //归并排序
		       case 4: heapSort(lo, hi); break; //堆排序（第12章）
	           default: quickSort(lo, hi); break; //快速排序（第14章）
		       
						  
		} //随机选择算法以充分测试。实用时可视具体问题的特点灵活确定或扩充
		
	}

	 template<typename T>
	  void Vector<T>::unsort(Rank lo, Rank hi) //随机置乱区间[lo, hi)
	 {
		 T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
		 for (Rank i = hi - lo; 1 < i; --i) //自后向前
		 {
			 swap(V[i - 1], V[rand() % i]);//将V[i - 1]与V[0, i)中某一元素随机交换
		 }
	 }

	  template<typename T>
	   int Vector<T>::deduplicate()  //删除无序向量中重复元素
	  {
		  Rank oldSize = _size; //记录原规模
		  for (Rank i = 1; i < _size; ) //自前向后逐个考查_elem[1,_size)
		  {
			  if (-1 == find(_elem[i], 0, i)) //在前缀[0,i)中寻找与[i]雷同者（至多一个），O(i)
			  {
				  i++;//若无雷同，则继续考查其后继
			  }
			  else
			  {
				  remove(i);//否则删除雷同者
			  }
		  }
		  return oldSize - _size; //被删除元素总数
	  }
	  
	   template<typename T>
	    int Vector<T>::uniquify()
	   {
		   Rank i = 0, j = 0; //各对互异“相邻”元素的秩
		   while (++j < _size) //逐一扫描，直至末元素
		   {
			   if (_elem[i] != _elem[j]) //跳过雷同者
			   {
				   _elem[++i] = _elem[j];//发现不同元素时，向前移至紧邻于前者右侧
			   }
		   }
		   _size = ++i; shrink(); //直接截除尾部多余元素
		   return j - i; //向量规模变化量，即被删除元素总数
	   }

		template<typename T>
		void Vector<T>::traverse(void(*visit)(T&))//借助函数指针机制
		{
			for (Rank i = 0; i < _size; i++) visit(_elem[i]);//遍历向量
		}

		template <typename T>
		template <typename VST> //元素类型、操作器
		void Vector<T>::traverse(VST& visit) //借助函数对象机制
		{
			for (Rank i = 0; i < _size; i++) visit(_elem[i]);//遍历向量
		}
