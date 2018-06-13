// BinaryTreeNode.h: interface for the BinaryTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYTREENODE_H__65C73C3B_E763_40D9_8460_F5703119C756__INCLUDED_)
#define AFX_BINARYTREENODE_H__65C73C3B_E763_40D9_8460_F5703119C756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T> class BinaryTree;
template <class T> class BinarySearchTree;

template <class T>
class BinaryTreeNode  
{
friend class BinaryTree<T>;
friend class BinarySearchTree<T>;
private:
	T  element;					               			//二叉树结点数据域
	BinaryTreeNode<T>*  left; 							//二叉树结点指向左子树的指针
	BinaryTreeNode<T>*  right; 							//二叉树结点指向左子树的指针

public:
	BinaryTreeNode();
	BinaryTreeNode(const T& ele);						//给定数据的构造函数
	BinaryTreeNode(const T& ele,BinaryTreeNode* l, BinaryTreeNode* r);//给定数据的左右指针的构造函数
	T  value() const;									//返回当前结点的数据
	BinaryTreeNode<T>& operator= (const BinaryTreeNode<T>& Node)
	{this=Node;};										//重载赋值操作符
	BinaryTreeNode<T>*  leftchild() const;				//返回当前结点指向左子树的指针
	BinaryTreeNode<T>*  rightchild() const;				//返回当前结点指向右子树的指针
    void  setLeftchild(BinaryTreeNode<T>*);				//设置当前结点的左子树
    void  setRightchild(BinaryTreeNode<T>*);			//设置当前结点的右子树

	void  setValue(const T& val);						//设置当前结点的数据域
	bool  isLeaf() const;								//判定当前结点是否为叶结点,若是返回true
};

  //***************************************************************************//
 //**********************Class BinaryTreeNode Implementation******************//
//***************************************************************************//

template<class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	left=right=NULL;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele)	//给定数据的构造函数
{
	element=ele;
	left=right=NULL;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele,BinaryTreeNode* l, BinaryTreeNode* r)
//给定数据的左右指针的构造函数
{
	element=ele;
	left=l;
	right=r;
}

template<class T>
T  BinaryTreeNode<T>::value() const
{
	return element; 
}	

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::leftchild() const
{
	return left;
}												//返回当前结点指向左子树的指针

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::rightchild() const
{
	return right;								//返回当前结点指向右子树的指针
}			

template<class T>
void  BinaryTreeNode<T>::setLeftchild(BinaryTreeNode<T>* subroot)//设置当前结点的左子树
{
	left=subroot;
}

template<class T>
void  BinaryTreeNode<T>::setRightchild(BinaryTreeNode<T>* subroot)//设置当前结点的右子树
{
	right=subroot;
}

template<class T>
void  BinaryTreeNode<T>::setValue(const T& val)	//设置当前结点的数据域
{
	element = val; 
} 									

template<class T>
bool  BinaryTreeNode<T>::isLeaf() const			//判定当前结点是否为叶结点,若是返回true
{
	return (left == NULL) && (right == NULL); 
}


#endif // !defined(AFX_BINARYTREENODE_H__65C73C3B_E763_40D9_8460_F5703119C756__INCLUDED_)
