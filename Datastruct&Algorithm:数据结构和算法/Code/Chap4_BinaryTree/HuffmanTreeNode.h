// HuffmanTreeNode.h: interface for the HuffmanTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUFFMANTREENODE_H__1DCB0787_7784_4184_818F_73CC69BEB78F__INCLUDED_)
#define AFX_HUFFMANTREENODE_H__1DCB0787_7784_4184_818F_73CC69BEB78F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BinaryTree1.h"

template<class T>
class HuffmanTreeNode:public BinaryTreeNode<T>
{
private:
	HuffmanTreeNode<T>* parent;
public:
	HuffmanTreeNode();
	virtual ~HuffmanTreeNode();

};

#endif // !defined(AFX_HUFFMANTREENODE_H__1DCB0787_7784_4184_818F_73CC69BEB78F__INCLUDED_)
