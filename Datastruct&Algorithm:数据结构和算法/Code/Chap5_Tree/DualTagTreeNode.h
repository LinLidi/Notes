// DualTagTreeNode.h: interface for the DualTagTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALTAGTREENODE_H__A47B985A_7B55_4393_8414_EDE585523BE7__INCLUDED_)
#define AFX_DUALTAGTREENODE_H__A47B985A_7B55_4393_8414_EDE585523BE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<class T>
class DualTagTreeNode  
{
public:
	T	info;							//树结点信息
	int	ltag;							//左标记
	int rtag;							//右标记
	DualTagTreeNode();
	virtual ~DualTagTreeNode();

};

template<class T>
DualTagTreeNode<T>::DualTagTreeNode()
{
		ltag=1;
		rtag=1;
}
template<class T>
DualTagTreeNode<T>::~DualTagTreeNode()
{
}

#endif // !defined(AFX_DUALTAGTREENODE_H__A47B985A_7B55_4393_8414_EDE585523BE7__INCLUDED_)
