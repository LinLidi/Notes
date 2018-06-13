// HuffmanTree.h: interface for the HuffmanTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUFFMANTREE_H__E2FE6C12_C0A9_4483_AF1B_9623F1FD0EF8__INCLUDED_)
#define AFX_HUFFMANTREE_H__E2FE6C12_C0A9_4483_AF1B_9623F1FD0EF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HuffmanTreeNode.h"
#include "MinHeap.h"

template <class T>
class HuffmanTree  
{
private:
	HuffmanTreeNode<T>* root;						//Huffman树的树根
	//把ht1和ht2为根的Huffman子树合并成一棵以parent为根的二叉树
	void MergeTree(HuffmanTreeNode<T> &ht1,HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T>* parent);
public:
	//构造Huffman树，weight是存储权值的数组，n是数组长度
	HuffmanTree(T weight[],int n);
	//删除Huffman树或其子树
	void DeleteTree(HuffmanTreeNode<T>* root);
	virtual ~HuffmanTree();							//析构函数
};

template <class T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> &ht1,HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T>* parent)
{
	parent->left=&ht1;
	parent->right=&ht2;
	parent->element=ht1.element+ht2.element;
	parent->parent=NULL;
	ht1.parent=ht2.parent=parent;
}

template <class T>
HuffmanTree<T>::HuffmanTree(T weight[],int n)
{
	MinHeap<HuffmanTreeNode<T>> heap(n);			//定义最小值堆
	HuffmanTreeNode<T> *parent,&firstchild,&secondchild;
	HuffmanTreeNode<T>* NodeList=new HuffmanTreeNode<T>[n];
	for(int i=0;i<n;i++)							//初始化
	{
		NodeList[i].element=weight[i];
		NodeList[i].parent=NodeList[i].left=NodeList[i].right=NULL;
		heap.Insert(NodeList[i]);					//向堆中添加元素
	}

	for(i=0;i<n-1;i++)			
	//通过n-1次合并建立Huffman树
	{
		parent=new HuffmanTreeNode<T>;
		firstchild=heap.RemoveMin();				//选择权值最小的结点
		secondchild=heap.RemoveMin();				//选择权值次小的结点
		MergeTree(firstchild,secondchild,parent);	//合并权值最小的两棵树
		heap.Insert(*parent);						//把parent插入到堆中去
		root=parent;								//建立根结点
	}
	delete []NodeList;
}

template <class T>
void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T>* root)
{
	if(root)
	{
		DeleteTree(root->left);
		DeleteTree(root->right);
		delete root;
	}
}

template <class T>
virtual HuffmanTree<T>::~HuffmanTree()
{
	DeleteTree(root);
}

#endif // !defined(AFX_HUFFMANTREE_H__E2FE6C12_C0A9_4483_AF1B_9623F1FD0EF8__INCLUDED_)
