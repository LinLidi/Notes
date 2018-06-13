// TreeNode.h: interface for the TreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREENODE_H__13C52CCB_6E4A_493C_9F1A_AA230FD1F057__INCLUDED_)
#define AFX_TREENODE_H__13C52CCB_6E4A_493C_9F1A_AA230FD1F057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T> class Tree;

template<class T>
class TreeNode  
{
friend class Tree<T>;
private:
	T m_Value;							//树结点的值
	TreeNode<T>*	pChild;				//左子结点
	TreeNode<T>*	pSibling;			//右兄弟结点
public:
  TreeNode();							//缺省构造函数
  TreeNode(const T&);					//拷贝构造函数
  ~TreeNode(){};						//析构函数
  bool isLeaf();					    //如果结点是叶，返回true
  T Value();							//返回结点的值 
  TreeNode<T>* LeftMostChild();			//返回第一个左孩子
  TreeNode<T>* RightSibling();			//返回右兄弟
  void setValue(T&);					//设置结点的值 
  void setChild(TreeNode<T>* pointer);	//设置左孩子
  void setSibling(TreeNode<T>* pointer);//设置右兄弟
  void InsertFirst(TreeNode<T>* node);	//以第一个孩子的身份插入结点
  void InsertNext(TreeNode<T>* node);	//以右兄弟的身份插入结点
};

template<class T>
TreeNode<T>::TreeNode()
{//缺省构造函数
		pChild=NULL;
		pSibling=NULL;
}
template<class T>
TreeNode<T>::TreeNode(const T& value)
{//拷贝构造函数
		m_Value=value;
		pChild=NULL;
		pSibling=NULL;
}

template<class T>
T TreeNode<T>::Value()
{//返回结点的值 
	return m_Value;
}

template<class T>
bool TreeNode<T>::isLeaf()
{//如果结点是叶，返回true
	if(NULL==pChild)
		return true;
	return false;
}

template<class T>
TreeNode<T>* TreeNode<T>::LeftMostChild()
{//返回第一个左孩子
	return pChild;
}

template<class T>
TreeNode<T>* TreeNode<T>::RightSibling()
{//返回右兄弟
	return pSibling;
}

template<class T>
void TreeNode<T>::setValue(T& value)
{//设置结点的值 
	m_Value=value;
}

template<class T>
void TreeNode<T>::setChild(TreeNode<T>* pointer)
{//设置左孩子
	pChild=pointer;
}

template<class T>
void TreeNode<T>::setSibling(TreeNode<T>* pointer)
{//设置右兄弟
	pSibling=pointer;
}

template<class T>
void TreeNode<T>::InsertFirst(TreeNode<T>* node)
{//以第一个孩子的身份插入结点
	if(!pChild)
		pChild=node;
	else
	{
		node->pSibling=pChild;
		pChild=node;
	}
}

template<class T>
void TreeNode<T>::InsertNext(TreeNode<T>* node)
{//以右兄弟的身份插入结点
	if(!pSibling)
		pSibling=node;
	else
	{
		node->pSibling=pSibling;
		pSibling=node;
	}
}

#endif // !defined(AFX_TREENODE_H__13C52CCB_6E4A_493C_9F1A_AA230FD1F057__INCLUDED_)
