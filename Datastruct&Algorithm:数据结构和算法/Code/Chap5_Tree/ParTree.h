// ParTree.h: interface for the ParTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTREE_H__CBF85D1A_1086_4E89_9CB6_BEE7FBE72DD0__INCLUDED_)
#define AFX_PARTREE_H__CBF85D1A_1086_4E89_9CB6_BEE7FBE72DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParTreeNode.h"

template<class T>
class ParTree  
{
public:
	ParTreeNode<T>* array;							//存储树结点的数组
	int	Size;										//数组大小
	ParTreeNode<T>*	Find(ParTreeNode<T>* node)const;//查找node结点的根结点
	ParTreeNode<T>*	FindPC(ParTreeNode<T>* node)const;//压缩路径方法查找node结点的根结点
	ParTree(const int size);						//构造函数
	virtual ~ParTree();								//析构函数
	void Union(int i,int j);						//把下标为i，j的结点合并为一棵子树
	bool Different(int i,int j);					//判定下标为i，j的结点是否在一棵树中
};

template <class T>
ParTree<T>::ParTree(const int size)
{
	Size=size;
	array=new ParTreeNode<T>[size];
}

template <class T>
ParTree<T>::~ParTree()
{
	delete []array;
}

template <class T>
ParTreeNode<T>*	ParTree<T>::Find(ParTreeNode<T>* node) const
{
	ParTreeNode<T>* pointer=node;
	while(pointer->getParent()!=NULL)
		pointer=pointer->getParent();
	return pointer;
}

template <class T>
ParTreeNode<T>*	ParTree<T>::FindPC(ParTreeNode<T>* node) const
{
	if(node->getParent()==NULL)
		return node;
	node->setParent(FindPC(node->getParent()));
	return node->getParent();
}

template<class T>
bool ParTree<T>::Different(int i,int j)
{
	ParTreeNode<T>* pointeri=Find(&array[i]);		//找到结点i的根
	ParTreeNode<T>* pointerj=Find(&array[j]);		//找到结点j的根
	return pointeri!=pointerj;
}

template<class T>
void ParTree<T>::Union(int i,int j)
{
	ParTreeNode<T>* pointeri=Find(&array[i]);		//找到结点i的根
	ParTreeNode<T>* pointerj=Find(&array[j]);		//找到结点j的根
	if(pointeri!=pointerj)
	{
		if(pointeri->getCount()>=pointerj->getCount())
		{
			pointerj->setParent(pointeri);
			pointeri->setCount(pointeri->getCount()+pointerj->getCount());
		}
		else
		{
			pointeri->setParent(pointerj);
			pointerj->setCount(pointeri->getCount()+pointerj->getCount());
		}
	}

}


#endif // !defined(AFX_PARTREE_H__CBF85D1A_1086_4E89_9CB6_BEE7FBE72DD0__INCLUDED_)
