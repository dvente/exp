//
// Created by daniel on 10-10-16.
//

#ifndef EXP_TREENODE_H
#define EXP_TREENODE_H

template <class T>class TreeNode{

public:
    /**
    * @function TreeNode (constructor)
    * @abstract creates a treenode object containing a pointer to its left and right (empty) child and its (empty) info
    * @param takes no parameters
    * @return does not return anything
    * @pre none
    * @post a object of class treenode is created containing...
    **/
    TreeNode();
    /**
    * @function ~TreeNode (destructor)
    * @abstract deletes the treenode
    * @param takes no parameters
    * @return does not return anything
    * @pre none
    * @post a object of class treenode is deleted and memory is free
    **/
    ~TreeNode();
    /**
    * @function getLeft
    * @abstract returns pointer to left child
    * @param takes no parameters
    * @return returns pointer to left child
    * @pre none
    * @post nothing is changed
    **/
    TreeNode<T>* getLeft() const;
    /**
    * @function getRight
    * @abstract returns pointer to right child
    * @param takes no parameters
    * @return returns pointer to right child
    * @pre none
    * @post nothing is changed
    **/
    TreeNode<T>* getRight() const;
    /**
    * @function setLeft
    * @abstract sets the left child of a treenode
    * @param takes the pointer to the treenode that is going to be the left child
    * @return returns nothing
    * @pre none
    * @post the left child pointer now points to the provided treenode
    **/
    void setLeft(TreeNode<T>* node);
    /**
    * @function setRight
    * @abstract sets the right child of a treenode
    * @param takes the pointer to the treenode that is going to be the right child
    * @return returns nothing
    * @pre none
    * @post the right child pointer now points to the provided treenode
    **/
    void setRight(TreeNode<T>* node);
    /**
    * @function setInfo
    * @abstract sets the info of a treenode
    * @param takes the value that is going to be the info of the treenode
    * @return returns nothing
    * @pre none
    * @post info now contains the provided value
    **/
    void setInfo(T value);
    /**
    * @function getInfo
    * @abstract returns the info of the treenode
    * @param takes no parameters
    * @return returns the info of the treenode
    * @pre none
    * @post nothing is changed
    **/
    T getInfo() const;
    /**
    * @function getKey
    * @abstract returns the key of the treenode so that we can make pictures in dotty
    * @param takes no parameters
    * @return returns the key of the treenode
    * @pre none
    * @post nothing is changed
    **/
    int getKey() const;
    /**
    * @function setKey
    * @abstract sets the key of the treenode
    * @param takes the new value of the key
    * @return returns nothing
    * @pre none
    * @post the key is set to the determined value
    **/
    void setKey(int value);

protected:
    T info; //info of the treenode
    int key; //key of the treenode
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

    left = NULL;
    right = NULL;
    key = 0;

}//TreeNode<T>::TreeNode

template <class T>
TreeNode<T>::~TreeNode(){

    delete left;
    delete right;

}//TreeNode<T>::TreeNode


#endif //EXP_TREENODE_H
