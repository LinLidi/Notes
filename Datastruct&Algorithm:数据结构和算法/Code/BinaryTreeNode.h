#ifndef BinaryTreeNode_h
#define BinaryTreeNode_h
#include <iostream>
using namespace std;

template <class T> class BinaryTree;
template <class T> class BinarySearchTree;

template <class T>
class BinaryTreeNode
{
    friend class BinaryTree<T>;
    friend class BinarySearchTree<T>;
private:
    T  value;
    BinaryTreeNode<T>*  leftchild;
    BinaryTreeNode<T>*  rightchild;
    
public:
    /////////////////////////////////三种构造函数/////////////////////////////////
    BinaryTreeNode();
    BinaryTreeNode(const T& v);
    BinaryTreeNode(const T& v,BinaryTreeNode* l, BinaryTreeNode* r);
    
    T  currentValue() const;
    BinaryTreeNode<T>*  leftchildTree() const;
    BinaryTreeNode<T>*  rightchildTree() const;
    
    void  setLeftchild(BinaryTreeNode<T>*);
    void  setRightchild(BinaryTreeNode<T>*);
    void  setValue(const T& val);
    bool  isLeaf() const;
    
    BinaryTreeNode<T>& operator= (const BinaryTreeNode<T>& Node){this=Node;};
};

template<class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
    leftchild = rightchild = NULL;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& v)
{
    value = v;
    leftchild = rightchild = NULL;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& v,BinaryTreeNode* l, BinaryTreeNode* r)
{
    value = v;
    leftchild = l;
    rightchild = r;
}

template<class T>
T  BinaryTreeNode<T>::currentValue() const
{
    return value;
}

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::leftchildTree() const
{
    return leftchild;
}

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::rightchildTree() const
{
    return rightchild;
}

template<class T>
void  BinaryTreeNode<T>::setLeftchild(BinaryTreeNode<T>* subroot)
{
    left = subroot;
}

template<class T>
void  BinaryTreeNode<T>::setRightchild(BinaryTreeNode<T>* subroot)
{
    right = subroot;
}

template<class T>
void  BinaryTreeNode<T>::setValue(const T& val)
{
    value = val;
}

template<class T>
bool  BinaryTreeNode<T>::isLeaf() const
{
    return (leftchild  == NULL) && (rightchild == NULL);
}



#endif /* BinaryTreeNode_h */
