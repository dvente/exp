//
// Created by daniel on 10-10-16.
//

#ifndef EXP_TREENODE_H
#define EXP_TREENODE_H

template <class T>class TreeNode{

public:

    TreeNode();
    ~TreeNode();
    TreeNode<T>* getLeft() const;
    TreeNode<T>* getRight() const;
    void setLeft(TreeNode<T>* node);
    void setRight(TreeNode<T>* node);
    void setInfo(T value);
    T getInfo() const;
    int getKey() const;
    void setKey(int value);
    bool operator==(const TreeNode &rhs) const;
    bool operator!=(const TreeNode &rhs) const;

protected:
    T info; //info of the treeNode
    int key; //key of the treeNode
    TreeNode<T> *left; //pointer to left child of the treenode
    TreeNode<T> *right; //pointer to right child of the treenode

};


template <class T>
void TreeNode<T>::setKey(int value){

    key = value;

}//TreeNode::setLeft

template <class T>
void TreeNode<T>::setInfo(T value){

    info = value;

}//TreeNode::setLeft

template <class T>
void TreeNode<T>::setRight(TreeNode<T>* node){

    right = node;

}//TreeNode::setLeft

template <class T>
void TreeNode<T>::setLeft(TreeNode<T>* node){

    left = node;

}//TreeNode::setLeft


template <class T>
int TreeNode<T>::getKey() const{

    return key;

}//TreeNode::getLeft

template <class T>
T TreeNode<T>::getInfo() const{

    return info;

}//TreeNode::getLeft

template <class T>
TreeNode<T>* TreeNode<T>::getRight() const{

    return right;

}//TreeNode::getLeft

template <class T>
TreeNode<T>* TreeNode<T>::getLeft() const{

    return left;

}//TreeNode::getLeft

template <class T>
TreeNode<T>::TreeNode(){

    left = nullptr;
    right = nullptr;
    key = 0;

}

template<class T>
//this check equality between subtrees not necessarily just nodes
bool TreeNode<T>::operator==(const TreeNode &rhs) const {

    bool leftNull = (left == nullptr || rhs.left == nullptr);
    bool righNull = (right == nullptr || rhs.right == nullptr);

    bool leftEq, rightEq;

    if (!leftNull)
        leftEq = (*left == *(rhs.left));
    else
        leftEq = (left == rhs.left);

    if (!righNull)
        rightEq = (*right == *(rhs.right));
    else
        rightEq = (right == rhs.right);


    return info == rhs.info && leftEq && rightEq;
}


template<class T>
bool TreeNode<T>::operator!=(const TreeNode &rhs) const {
    return !(rhs == *this);
}
//TreeNode<T>::TreeNode

template <class T>
TreeNode<T>::~TreeNode(){

    delete left;
    delete right;

}//TreeNode<T>::TreeNode


#endif //EXP_TREENODE_H
