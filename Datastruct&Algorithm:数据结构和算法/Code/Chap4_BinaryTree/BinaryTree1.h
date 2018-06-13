// BinaryTree1.h: interface for the BinaryTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYTREE1_H__99C2FAA0_E42F_4CB0_8B01_C36F1FA6F1EE__INCLUDED_)
#define AFX_BINARYTREE1_H__99C2FAA0_E42F_4CB0_8B01_C36F1FA6F1EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BinaryTreeNode.h"
#include <stack>
#include <queue>

enum Tags{Left,Right};

template <class T>
class StackElement
{
public:
	BinaryTreeNode<T>* pointer;
	Tags tag;
};	

template <class T>
class BinaryTree  
{
protected:
	BinaryTreeNode<T>*  root;      							//二叉树根结点指针
public:
	BinaryTree(){root=NULL;};								//构造函数
	virtual ~BinaryTree(){DeleteBinaryTree(root);};			//析构函数
	BOOL isEmpty() const							
	{return ((root)?TRUE:FALSE);};							//判定二叉树是否为空树
	BinaryTreeNode<T>* getRoot(){return root;};
	void Initialize(BinaryTreeNode<T>* pointer){root=pointer;};
	//从二叉树的root结点开始，查找current结点的父结点
	BinaryTreeNode<T>* GetParent(BinaryTreeNode<T>* root,BinaryTreeNode<T>* current);
	//返回current结点的父结点指针
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
	//返回current结点的左兄弟
	BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
	//返回current结点的右兄弟
	BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current);
	//以elem作为根结点，leftTree作为树的左子树，rightTree作为树的右子树，构造一棵新的二叉树
	void CreateTree(const T& elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);
	//删除二叉树或其子树
	void DeleteBinaryTree(BinaryTreeNode<T>* root);				
	//前序遍历二叉树或其子树
	void PreOrder(BinaryTreeNode<T>* root);
	//中序遍历二叉树或其子树
	void InOrder(BinaryTreeNode<T>* root);
	//后序遍历二叉树或其子树
	void PostOrder(BinaryTreeNode<T>* root);
	//非递归前序遍历二叉树或其子树
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);
	//非递归中序遍历二叉树或其子树
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);
	//非递归后序遍历二叉树或其子树
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);
	//非递归后序遍历二叉树或其子树, 另一个版本
	void PostOrderWithoutRecusion2(BinaryTreeNode<T>* root);
	//按层次遍历二叉树或其子树
	void LevelOrder(BinaryTreeNode<T>* root);
};

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::GetParent(BinaryTreeNode<T>* root,BinaryTreeNode<T>* current)
{
	//从二叉树的root结点开始，查找current结点的父结点
	BinaryTreeNode<T>* temp;
	if(root==NULL)
		return NULL;
	//找到父结点
	if((root->leftchild()==current)||(root->rightchild()==current))
		return root;
	//递归寻找父结点
	if((temp=GetParent(root->leftchild(),current))!=NULL)
		return temp;
	else return GetParent(root->rightchild(),current);	
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
{//返回current结点的父结点指针
	if((current==NULL)||(current==root))
		return NULL;					//空结点或者current为根结点时，返回NULL
	return GetParent(root,current);		//调用递归函数寻找父结点
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::LeftSibling(BinaryTreeNode<T>* current)
{//返回current结点的左兄弟
	if(current)											//current不为空
	{
			BinaryTreeNode<T>* temp=Parent(current);	//返回current结点的父结点
			if((temp==NULL)||current==temp->leftchild())
				return  NULL;		    //如果父结点为空，或者current没有左兄弟
			else return temp->leftchild();
	}
	return NULL;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::RightSibling(BinaryTreeNode<T>* current)
{//返回current结点的右兄弟
	if(current)									//current不为空
	{
			BinaryTreeNode<T>* temp=Parent(current);//返回current结点的父结点
			if((temp==NULL)||current==temp->rightchild())
				return  NULL;					//如果父结点为空，或者current没有右兄弟
			else return temp->rightchild();
	}
	return NULL;
}

template<class T>
void BinaryTree<T>::CreateTree(const T& elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree)
{//以elem作为根结点，leftTree作为树的左子树，rightTree作为树的右子树，构造一棵新的二叉树
	root=new BinaryTreeNode<T>(elem,leftTree.root,rightTree.root);  //创建新树
	leftTree.root=rightTree.root=NULL;								//原来两棵子树的根结点指空，避免访问

}

template<class T>
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root)		//删除二叉树或其子树
{
	if(root)
	{
		DeleteBinaryTree(root->left);
		DeleteBinaryTree(root->right);
		delete root;
	};
};

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root)				//前序遍历二叉树或其子树
{
	if(root!=NULL)
	{
		AfxMessageBox(root->value());			//访问当前结点
		PreOrder(root->leftchild());			//访问左子树
		PreOrder(root->rightchild());			//访问右子树
	}
};

template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root)				//中序遍历二叉树或其子树
{
	if(root!=NULL)
	{
		InOrder (root->leftchild());			//访问左子树
		AfxMessageBox(root->value());			//访问当前结点
		InOrder (root->rightchild());			//访问右子树
	}
}

template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root)				//后序遍历二叉树或其子树
{
	if(root!=NULL)
	{
		PostOrder(root->leftchild());			//访问左子树
		PostOrder (root->rightchild());			//访问右子树
		AfxMessageBox(root->value());			//访问当前结点
	}
}

template<class T>
void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode<T>* root)//非递归前序遍历二叉树或其子树
{
	using std::stack;
	
	stack<BinaryTreeNode<T>* > aStack;
  	BinaryTreeNode<T>* pointer=root;       			//保存输入参数	

	while(!aStack.empty()||pointer)				
	{
	 if(pointer){
		  	  AfxMessageBox(pointer->value());		//访问当前结点
			  aStack.push(pointer);					//当前结点地址入栈
			  pointer=pointer->leftchild();			//当前链接结构指向左孩子
		  }
	 else {	        							    //左子树访问完毕，转向访问右子树
			  pointer=aStack.top();					//栈顶元素退栈                 
			  aStack.pop();
			  pointer=pointer->rightchild();		//当前链接结构指向右孩子
		   } //else
   } //while
}

template<class T>
void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T>* root)	//非递归中序遍历二叉树或其子树
{
	using std::stack;
	stack<BinaryTreeNode<T>* > aStack;
  	BinaryTreeNode<T>* pointer=root;				//保存输入参数	

	while(!aStack.empty()||pointer)				
	{
	 if(pointer){
			  aStack.push(pointer);					//当前结点地址入栈
			  pointer=pointer->leftchild();			//当前链接结构指向左孩子
		  }
	 else {        								    //左子树访问完毕，转向访问右子树
			  pointer=aStack.top();				
		  	  AfxMessageBox(pointer->value());		//访问当前结点
			  pointer=pointer->rightchild(); 		//当前链接结构指向右孩子
			  aStack.pop();							//栈顶元素退栈                 
		   } //else
   } //while
}

template<class T>
void BinaryTree<T>::PostOrderWithoutRecusion(BinaryTreeNode<T>* root)//非递归后序遍历二叉树或其子树
{
	using std::stack;
	StackElement<T> element;
	stack<StackElement<T > > aStack;
	BinaryTreeNode<T>* pointer;
	if(NULL==root)
		return;										//空树即返回
	else pointer=root;
	while(true)
	{
		//进入左子树
		while(pointer!=NULL)
		{
			element.pointer=pointer;
			element.tag=Left;
			aStack.push(element);
			pointer=pointer->leftchild();
		}
		//托出栈顶元素
		element=aStack.top();
		aStack.pop();
		pointer=element.pointer;
		//从右子树回来
		while(element.tag==Right)
		{
		  	  AfxMessageBox(pointer->value());	//访问当前结点
			  if(aStack.empty())
				  return;
			  else
			  {
				element=aStack.top();
				aStack.pop();
				pointer=element.pointer;
			  }
		}
		//从左子树回来
		element.tag=Right;
		aStack.push(element);
		pointer=pointer->rightchild();
	}
}

template<class T>
void BinaryTree<T>::PostOrderWithoutRecusion2(BinaryTreeNode<T>* root)
{//非递归后序遍历二叉树或其子树, 另一个版本
	using std::stack;
	stack<BinaryTreeNode<T>* > aStack;
	BinaryTreeNode<T> *p, *q;
	if(root==NULL)
		return;
	p=root;
	do{
		while(p!=NULL)							//沿左路分支下降			
		{
			aStack.push(p);
			p=p->leftchild();
		}
		q=NULL;
		while(!aStack.empty())
		{
			p=aStack.top();
			aStack.pop();
			if(p->rightchild()==q)				//右子树为空或刚刚被访问过
			{
		  	  AfxMessageBox(p->value());	//访问当前结点
			  q=p;
			}
			else
			{
				aStack.push(p);
				p=p->rightchild();
				break;
			}
		}
	}while(!aStack.empty());
}

template<class T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root)	//按层次遍历二叉树或其子树
{
	using std::queue;
	queue<BinaryTreeNode<T>*> aQueue;
	BinaryTreeNode<T>* pointer=root;
	
	if(pointer)
		aQueue.push(pointer);
	while(!aQueue.empty())
	{
		pointer=aQueue.front();
        AfxMessageBox(pointer->value());				//访问当前结点
		aQueue.pop();
		if(pointer->leftchild())
			aQueue.push(pointer->leftchild());
		if(pointer->rightchild())
			aQueue.push(pointer->rightchild());
	}
}

#endif // !defined(AFX_BINARYTREE1_H__99C2FAA0_E42F_4CB0_8B01_C36F1FA6F1EE__INCLUDED_)
