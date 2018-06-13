// ThreadBinaryTreeNode.h: interface for the ThreadBinaryTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADBINARYTREENODE_H__C8A1F5EE_AE5A_4117_AFA5_53BB64912CA5__INCLUDED_)
#define AFX_THREADBINARYTREENODE_H__C8A1F5EE_AE5A_4117_AFA5_53BB64912CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T> class ThreadBinaryTree;

template <class T>
class ThreadBinaryTreeNode  
{
friend class ThreadBinaryTree<T>;
private:
	int lTag,rTag;							//左右标志位
	ThreadBinaryTreeNode<T> *left,*right;	//线索或左右子树
	T	element;
public:
	ThreadBinaryTreeNode();
	//构造函数
	ThreadBinaryTreeNode(const T&):element(T),left(NULL),right(NULL),lTag(0),rTag(0){};
	//给定数据的左右指针的构造函数
	ThreadBinaryTreeNode(const T& ele,ThreadBinaryTreeNode<T>* l,int leftTag, ThreadBinaryTreeNode<T>* r,int rightTag);
	T value() const{return element;};						 		
	ThreadBinaryTreeNode<T>* leftchild()const {return left;};	
	ThreadBinaryTreeNode<T>* rightchild()const {return right;};
	void setValue(const T& type){element=type;};
	virtual ~ThreadBinaryTreeNode(){};						//析构函数
};

template<class T>
ThreadBinaryTreeNode<T>::ThreadBinaryTreeNode(const T& ele,ThreadBinaryTreeNode<T>* l,int leftTag, ThreadBinaryTreeNode<T>* r,int rightTag)
//给定数据的左右指针的构造函数
{
	element=ele;
	left=l;
	lTag=leftTag;
	right=r;
	rTag=rightTag;
}

#endif // !defined(AFX_THREADBINARYTREENODE_H__C8A1F5EE_AE5A_4117_AFA5_53BB64912CA5__INCLUDED_)
