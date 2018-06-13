// Tree.h: interface for the Tree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE_H__703FFCCE_C340_4198_98E7_00F503CF8261__INCLUDED_)
#define AFX_TREE_H__703FFCCE_C340_4198_98E7_00F503CF8261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeNode.h"
#include "DualTagTreeNode.h"
#include "LeftLinkTreeNode.h"
#include <queue>
#include <stack>

template <class T>
class Tree  
{
private:
	TreeNode<T>* root;								//树根结点
													//返回current父节点,由Parent调用
	TreeNode<T>* getParent(TreeNode<T>* root,TreeNode<T>* current);
	void DestroyNodes(TreeNode<T>*root);			//删除root为根的子树

public:
	Tree();											//构造函数
	Tree(DualTagTreeNode<T>* nodeArray,int count);	//构造函数,利用双标记位先根次序构造树
	Tree(LeftLinkTreeNode<T>* nodeArray,int count);	//构造函数,利用左链层次顺序构造树

	virtual ~Tree();								//析构函数
	TreeNode<T>* getRoot();							//返回树中的根结点
	void CreateRoot(const T& rootValue);			//创建树的根结点，使根结点元素的值为rootValue
	bool isEmpty();									//判断是否为空树，若是则返回true
	TreeNode<T>* Parent(TreeNode<T>* current);	    //返回current父节点
	TreeNode<T>* PrevSibling(TreeNode<T>* current); //返回current的前一个邻居结点
	TreeNode<T>* PrevSibling2(TreeNode<T>* current); //返回current的前一个邻居结点
	void DeleteSubTree(TreeNode<T>* subroot);		//释放以root为根的子树的所有结点
	void RootFirstTraverse(TreeNode<T>* root);		//先根深度优先周游树
	void RootLastTraverse(TreeNode<T>* root);		//后根深度优先周游树
	void WidthTraverse(TreeNode<T>* root);			//宽度优先周游树
	void WidthTraverse2(TreeNode<T>* root);			//宽度优先周游树:版本2
};

template <class T>
Tree<T>::Tree()
{//构造函数
	root=NULL;
}

template <class T>
Tree<T>::Tree(DualTagTreeNode<T>* nodeArray,int count)
{
	//使用STL中的stack
	using std::stack;
	stack<TreeNode<T>* > aStack;
	//准备建立根结点
	TreeNode<T>* pointer=new TreeNode<T>;
	root=pointer;
	//处理一个结点
	for(int i=0;i<count-1;i++)
	{
		pointer->setValue(nodeArray[i].info);
		if(nodeArray[i].rtag==0)
			aStack.push(pointer);
		else
			pointer->setSibling(NULL);

		TreeNode<T>* temppointer=new TreeNode<T>;
		if(nodeArray[i].ltag==0)
			pointer->setChild(temppointer);
		else
		{
			pointer->setChild(NULL);
			pointer=aStack.top();
  			aStack.pop();		
			pointer->setSibling(temppointer);
		}
		pointer=temppointer;
	}
	//处理最后一个结点
	pointer->setValue(nodeArray[count-1].info);
	pointer->setChild(NULL);
	pointer->setSibling(NULL);
}

template <class T>
Tree<T>::Tree(LeftLinkTreeNode<T>* nodeArray,int count)
{//构造函数,利用左链层次顺序构造树
	using std::queue;							//使用STL队列
	queue<TreeNode<T>*> aQueue;

	//准备建立根结点
	TreeNode<T>* pointer=new TreeNode<T>;
	root=pointer;

	int currentIndex=-1;

	while(pointer||!aQueue.empty())
	{
		if(pointer)
		{
			currentIndex++;
			pointer->setValue(nodeArray[currentIndex].info);
			if(nodeArray[currentIndex].llink)
			{
				TreeNode<T>* leftpointer=new TreeNode<T>;				
				pointer->setChild(leftpointer);
				aQueue.push(leftpointer);
			} 
			else pointer->setChild(NULL);

			if(nodeArray[currentIndex].rtag==0)
			{
				TreeNode<T>* rightpointer=new TreeNode<T>;				
				pointer->setSibling(rightpointer);
			}
			else pointer->setSibling(NULL);

			pointer=pointer->RightSibling();//访问pointer的兄弟
		}
		else
		{
			pointer=aQueue.front();
			aQueue.pop();
		}
	}
}

template <class T>
Tree<T>::~Tree()
{//析构函数
	while(root)
		DeleteSubTree(root);
}

template <class T>
TreeNode<T>* Tree<T>::getRoot()
{//返回树中的根结点
		return root;
}

template <class T>
void Tree<T>::CreateRoot(const T& rootValue)
{//创建树的根结点，使根结点元素的值为rootValue
	if(!root)
		root=new TreeNode<T>(rootValue);
}

template <class T>
bool Tree<T>::isEmpty()
{//判断是否为空树，若是则返回true
	if(root)
		return false;
	return true;
}

template <class T>
void Tree<T>::RootFirstTraverse(TreeNode<T>* root)
{//先根深度优先周游树
	while(NULL!=root)
	{
		AfxMessageBox(root->Value());				//访问当前结点
		RootFirstTraverse(root->LeftMostChild());	//访问头一棵树树根的子树
		root=root->RightSibling();					//周游其他的树
	}
}

template <class T>
void Tree<T>::RootLastTraverse(TreeNode<T>* root)
{//后根深度优先周游树
	while(NULL!=root)
	{
		RootLastTraverse(root->LeftMostChild());	//访问头一棵树树根的子树
		AfxMessageBox(root->Value());				//访问当前结点
		root=root->RightSibling();					//周游其他的树
	}
}

template <class T>
void Tree<T>::WidthTraverse(TreeNode<T>* root)
{
	using std::queue;
	queue<TreeNode<T>*> aQueue;
	TreeNode<T>* pointer=root;
	if(pointer)
	{
		aQueue.push(pointer);
		while(!aQueue.empty())
		{
			pointer=aQueue.front();
			AfxMessageBox(pointer->Value());
			while(pointer->RightSibling())
			{
				if(pointer->LeftMostChild())
					aQueue.push(pointer->LeftMostChild());
				pointer=pointer->RightSibling();
				AfxMessageBox(pointer->Value());
			}
			if(pointer->LeftMostChild())
				aQueue.push(pointer->LeftMostChild());
			aQueue.pop();
		}
	}
}

template <class T>
void Tree<T>::WidthTraverse2(TreeNode<T>* root)
{//宽度优先周游树:版本2
	using std::queue;							//使用STL队列
	queue<TreeNode<T>*> aQueue;
	TreeNode<T>* pointer=root;
	if(pointer)
	{
		while(NULL!=pointer)
		{
			aQueue.push(pointer);
			pointer=pointer->RightSibling();
		}
		while(!aQueue.empty())
		{
			pointer=aQueue.front();
			aQueue.pop();
			AfxMessageBox(pointer->Value());
			pointer=pointer->LeftMostChild();
			while(pointer)
			{
				aQueue.push(pointer);
				pointer=pointer->RightSibling();
			}
		}
	}
}

template <class T>
TreeNode<T>* Tree<T>::PrevSibling(TreeNode<T>* current)
{//返回current的前一个邻居结点
	using std::queue;								//使用ATL的队列
	queue<TreeNode<T>*> aQueue;
	TreeNode<T>* pointer=root;
	TreeNode<T>* prev=NULL;

	if(pointer)
	{
		aQueue.push(pointer);
		while(!aQueue.empty())
		{
			pointer=aQueue.front();				 	//取队列首结点
			if(pointer==current)
				return prev;
			while(pointer->RightSibling())
			{
				prev=pointer;
				pointer=pointer->pSibling;
				if(pointer==current)
					return prev;
				else 
				{
					if(prev->LeftMostChild())
						aQueue.push(prev->LeftMostChild());
				}
			}
			if(pointer->LeftMostChild())
				aQueue.push(pointer->LeftMostChild());
			aQueue.pop();
			prev=NULL;
		}
			
	}
	return NULL;
}

template <class T>
TreeNode<T>* Tree<T>::PrevSibling2(TreeNode<T>* current)
{//返回current的前一个邻居结点
	using std::queue;								//使用ATL的队列
	queue<TreeNode<T>*> aQueue;
	TreeNode<T>* pointer=root;
	TreeNode<T>* prev=NULL;
	if((NULL==current)||(NULL==pointer)||(current==pointer))
		return NULL;
	while(pointer)
	{
		if(pointer==current)
			return prev;
		aQueue.push(pointer);
		prev=pointer;
		pointer=pointer->pSibling;
	}
	while(!aQueue.empty())
	{
		prev=NULL;
		pointer=aQueue.front();				 	//取队列首结点
		aQueue.pop();
		pointer=pointer->LeftMostChild();
		while(pointer)
		{
			if(pointer==current)
				return prev;
			aQueue.push(pointer);
			prev=pointer;
			pointer=pointer->pSibling;
		}
	}
	return NULL;
}

template <class T>
TreeNode<T>* Tree<T>::getParent(TreeNode<T>* root,TreeNode<T>* current)
{//返回current父节点,由Parent调用
	TreeNode<T>* temp;
	if(root==NULL)
		return NULL;
	//找到父结点
	if(root->LeftMostChild()==current)
		return root;
	//递归寻找父结点
	if((temp=getParent(root->LeftMostChild(),current))!=NULL)
		return temp;
	else return getParent(root->RightSibling(),current);	

}

template <class T>
TreeNode<T>* Tree<T>::Parent(TreeNode<T>* current)
{//返回current父节点
	TreeNode<T>* pointer=current;
	if(NULL!=pointer)
	{
		TreeNode<T>* leftmostChild=NULL;
		while((leftmostChild=PrevSibling(pointer))!=NULL)
			pointer=leftmostChild;
		leftmostChild=pointer;
		pointer=root;
		if(leftmostChild==root)
			return NULL;
		else return getParent(pointer,leftmostChild);
	}
}

template <class T>
void Tree<T>::DestroyNodes(TreeNode<T>* root)
{//删除root为根的子树的结点
	if(root)
	{
		DestroyNodes(root->LeftMostChild());		//递归删除root的以左子结点为根的子树
		DestroyNodes(root->RightSibling());		    //递归删除root的以右兄弟结点为根的子树
		delete root;								//删除根结点
	}

}

template <class T>
void Tree<T>::DeleteSubTree(TreeNode<T>* subroot)
{//释放以subroot为根的子树的所有结点
	TreeNode<T>* pointer=PrevSibling(subroot);
	if(NULL==pointer)
	{
		pointer=Parent(subroot);
		if(pointer)
		{
			pointer->pChild=subroot->RightSibling();
			subroot->pSibling=NULL;
		}
		else
		{
			root=subroot->RightSibling();
			subroot->pSibling=NULL;
			
		}
	}
	else
	{
		pointer->pSibling=subroot->RightSibling();
		subroot->pSibling=NULL;
	}
	DestroyNodes(subroot);
}

#endif // !defined(AFX_TREE_H__703FFCCE_C340_4198_98E7_00F503CF8261__INCLUDED_)
