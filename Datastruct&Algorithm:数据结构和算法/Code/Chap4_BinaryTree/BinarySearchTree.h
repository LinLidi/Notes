// BinarySearchTree.h: interface for the BinarySearchTree class.
//
//////////////////////////////////////////////////////////////////////
#include "BinaryTreeNode.h"
#include "BinaryTree1.h"

#if !defined(AFX_BINARYSEARCHTREE_H__1CD2FF9D_73F2_4194_974A_12892DFB325F__INCLUDED_)
#define AFX_BINARYSEARCHTREE_H__1CD2FF9D_73F2_4194_974A_12892DFB325F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T>
class BinarySearchTree:public BinaryTree<T> 
{
public:
	BinarySearchTree(){};
	virtual ~BinarySearchTree(){};
	void InsertNode(BinaryTreeNode<T>* root,BinaryTreeNode<T>* newpointer);
	void DeleteNode(BinaryTreeNode<T>* pointer);
	void DeleteNodeEx(BinaryTreeNode<T>* pointer);
};
template <class T>
void BinarySearchTree<T>::InsertNode(BinaryTreeNode<T>* root,BinaryTreeNode<T>* newpointer)
{
	BinaryTreeNode<T>* pointer=NULL;
	//初始化
	if(NULL==root)
	{
		//用指针newpointer初始化二叉搜索树树根，赋值实现
		Initialize(newpointer);
		return;
	}
	else pointer=root;
	while(1)
	{
		if(newpointer->value()==pointer->value())
			return ;									//相等则不用插入
		else if(newpointer->value()<pointer->value())	//作为左子树
		{
			if(pointer->leftchild()==NULL)				
			{
				pointer->left=newpointer;
				return;
			}
			else	pointer=pointer->leftchild();

		}
		else{											//作为右子树
			if(pointer->rightchild()==NULL)
			{
				pointer->right=newpointer;
				return;
			}
			else	pointer=pointer->rightchild();
		}
	}
}
template <class T>
void BinarySearchTree<T>::DeleteNode(BinaryTreeNode<T>* pointer)
{//二叉搜索树的删除
	BinaryTreeNode<T>* temppointer=NULL;	
	if(!pointer)
		return;
	BinaryTreeNode<T>* parent=GetParent(root,pointer);
	//被删结点无左子树吗？
	if(NULL==pointer->leftchild())
	{
		//被删除结点是根结点吗？
		if(NULL==parent)
			root=pointer->rightchild();
		else if(parent->leftchild()==pointer)
			parent->left=pointer->rightchild();
		else
			parent->right=pointer->rightchild();
		delete pointer;
		pointer=NULL;
		return;
	}
	else temppointer=pointer->leftchild();
	//在左子树中找对称序的最后一个结点
	while(temppointer->rightchild()!=NULL)
		temppointer=temppointer->rightchild();
	//被删除结点的右子树作为temppointer的右子树
	temppointer->right=pointer->rightchild();
	//被删除结点的左子树根代替被删除结点
	if(parent==NULL)
		root=pointer->leftchild();
	else if(parent->leftchild()==pointer)
		parent->left=pointer->leftchild();
	else 
		parent->right=pointer->leftchild();
	delete pointer;
	pointer=NULL;
	return;
}

template <class T>
void BinarySearchTree<T>::DeleteNodeEx(BinaryTreeNode<T>* pointer)
{
	//如果带删除节点不存在,返回
	if( pointer == NULL )
		return;
	//保存要替换上来的节点
	BinaryTreeNode<T> * temppointer;
	//保存要替换上来的节点的父节点
	BinaryTreeNode<T> * tempparent = NULL;
	//保存要删除节点的父节点
	BinaryTreeNode<T> * parent = GetParent(root ,pointer );

	//如果待删除节点的左子树为空,就将它的右子树代替它即可
	if( pointer->leftchild() == NULL )
	{
		//将右子树连到待删除节点的父的合适位置
		if( parent == NULL )
			root = pointer->rightchild();
		else if( parent->leftchild() == pointer )
			parent->left = pointer->rightchild();
		else
			parent->right = pointer->rightchild();
		delete pointer;
		pointer=NULL;
		return;
	}

	//当待删除节点左子树不为空,就在左子树中寻找最大节点替换待删除节点
	temppointer = pointer->leftchild();
	while(temppointer->rightchild() != NULL )
	{
		tempparent = temppointer;
		temppointer = temppointer->rightchild();
	}

	//删除替换结点
	if(tempparent==NULL)
		pointer->left=temppointer->leftchild();
	else
		tempparent->right=temppointer->leftchild();

	//用替换结点去替代真正的删除结点
	if(parent==NULL)
		root=temppointer;
	else if( parent->leftchild() == pointer )
		     parent->left=temppointer;
		 else parent->right=temppointer;

	temppointer->left=pointer->leftchild();
	temppointer->right=pointer->rightchild();

	delete pointer;
	pointer=NULL;
	return;
}

#endif // !defined(AFX_BINARYSEARCHTREE_H__1CD2FF9D_73F2_4194_974A_12892DFB325F__INCLUDED_)
