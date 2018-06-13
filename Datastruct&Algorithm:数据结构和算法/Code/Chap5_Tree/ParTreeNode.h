// ParTreeNode.h: interface for the ParTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTREENODE_H__3A24E23B_0E76_4DF3_9EC1_75461437404A__INCLUDED_)
#define AFX_PARTREENODE_H__3A24E23B_0E76_4DF3_9EC1_75461437404A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class T>
class ParTreeNode  
{
private:
	T				value;							//结点的值
	ParTreeNode<T>* parent;							//父结点指针
	int		nCount;									//以此结点为根的子树的总结点个数
public:
	ParTreeNode();									//构造函数
	virtual ~ParTreeNode(){};						//析构函数
	T	getValue();									//返回结点的值
	void  setValue(const T& val);					//设置结点的值
	ParTreeNode<T>*  getParent();					//返回父结点指针
	void  setParent(ParTreeNode<T>* par);			//设置父结点指针
	int  getCount();								//返回结点数目
	void  setCount(const int count);				//设置结点数目
};

template<class T>
ParTreeNode<T>::ParTreeNode()
{
	parent=NULL;
	nCount=1;
}
template<class T>
T ParTreeNode<T>::getValue()
{
	return value;
}
template<class T>
void ParTreeNode<T>::setValue(const T& val)
{
	value=val;
}
template<class T>
ParTreeNode<T>* ParTreeNode<T>::getParent()
{
	return parent;
}
template<class T>
void ParTreeNode<T>::setParent(ParTreeNode<T>* par)
{
	parent=par;
}
template<class T>
int ParTreeNode<T>::getCount()
{
	return nCount;
}
template<class T>
void ParTreeNode<T>::setCount(const int count)
{
	nCount=count;
}


#endif // !defined(AFX_PARTREENODE_H__3A24E23B_0E76_4DF3_9EC1_75461437404A__INCLUDED_)
