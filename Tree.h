/**
* klassenaam: Tree
* @author Daniel Vente (1207318)
* @author Heleen Otten (1235672)
* @file Tree.h
* @date 13-10-2015
**/

#ifndef Tree_h
#define Tree_h

#include <fstream>
#include <string>
#include "TreeNode.h"

template<class T>
class Tree {
public:

    Tree();
    ~Tree();
    bool insert(T info);
    bool contains(T info) const;
    void showPreOrder(std::ostream &out) const;
    void showInOrder(std::ostream &out) const;
    void showPostOrder(std::ostream &out) const;
    bool saveAsDot(std::string filename) const;
    int getSize() const;
    void setSize(int size);

    TreeNode<T> *root;
protected:
    //variable for the root node
    bool insertNode(TreeNode<T> *current, T info);
    bool nodeContains(T info, const TreeNode<T> *parent) const;
    void nodeShowInOrder(std::ostream &out, const TreeNode<T> *parent) const;
    void nodeShowPreOrder(std::ostream &out, const TreeNode<T> *parent) const;
    void nodeShowPostOrder(std::ostream &out, const TreeNode<T> *parent) const;
    void nodeSaveAsDot(std::ofstream &file, const TreeNode<T> *parent) const;
    int size;
};

template<class T>
Tree<T>::Tree() {

    root = new TreeNode<T>;
    size = 0;

}//TreeNode::TreeNode

template<class T>
Tree<T>::~Tree() {

    delete root;//recursively delete the tree

}//TreeNode::TreeNode

template<class T>
bool Tree<T>::nodeContains(T info, const TreeNode<T> *parent) const {

    if (info == parent->getInfo())
        return true;
    else {//not found so check children
        if (parent->getLeft() != nullptr) {
            if (nodeContains(info, parent->getLeft()))
                return true;
        }//if
        else if (parent->getRight() != nullptr)
            return nodeContains(info, parent->getRight());
    }//else

    return false;//children don't contain it, so return false

}//Tree:nodeContains

template<class T>
bool Tree<T>::insert(T info) {

    return insertNode(root, info) && !contains(info);

}//Tree:insert

template<class T>
bool Tree<T>::insertNode(TreeNode<T> *current, T info) {

    if (root == nullptr) {
        root = new TreeNode<T>;
        root->setInfo(info);
        root->setKey(1);
        size = 1;
        return true;
    }// if

    while (current->getLeft() != nullptr)
        current = current->getLeft();

    TreeNode<T> *temp = new TreeNode<T>;
    current->setLeft(temp);
    temp->setInfo(info);
    temp->setKey(current->getKey() + 1);
    size++;
    return true;


}//Tree::insertNode

template<class T>
bool Tree<T>::contains(T info) const {
    return root != nullptr && nodeContains(info, root);

}//Tree:Contains

template<class T>
void Tree<T>::nodeShowInOrder(std::ostream &out, const TreeNode<T> *parent) const {

    if (parent->getLeft() != nullptr)
        nodeShowInOrder(out, parent->getLeft());

    out << parent->getInfo() << ", ";

    if (parent->getRight() != nullptr)
        nodeShowInOrder(out, parent->getRight());

}//Tree::nodeShowInOrder

template<class T>
void Tree<T>::nodeShowPreOrder(std::ostream &out, const TreeNode<T> *parent) const {

    out << parent->getInfo() << ", ";

    if (parent->getLeft() != nullptr)
        nodeShowPreOrder(out, parent->getLeft());

    if (parent->getRight() != nullptr)
        nodeShowPreOrder(out, parent->getRight());

}//Tree::nodeShowPreOrder

template<class T>
void Tree<T>::nodeShowPostOrder(std::ostream &out, const TreeNode<T> *parent) const {

    if (parent->getLeft() != nullptr)
        nodeShowPostOrder(out, parent->getLeft());

    if (parent->getRight() != nullptr)
        nodeShowPostOrder(out, parent->getRight());

    out << parent->getInfo() << ", ";

}//Tree::nodeShowPostOrder

template<class T>
void Tree<T>::showInOrder(std::ostream &out) const {

    nodeShowInOrder(out, root);

}//Tree::showInOrder


template<class T>
void Tree<T>::showPreOrder(std::ostream &out) const {

    nodeShowPreOrder(out, root);

}//Tree::showPreOrder


template<class T>
void Tree<T>::showPostOrder(std::ostream &out) const {

    nodeShowPostOrder(out, root);

}//Tree::showPostOrder

template<class T>
bool Tree<T>::saveAsDot(const std::string filename) const {

    std::ofstream file;
    file.open(filename.c_str());

    if (file.is_open()) {

        file << "digraph G {" << std::endl;
        nodeSaveAsDot(file, root);
        file << "}";
        file.close();
        return true;

    }//if
    else
        return false;

}//Tree::saveAsDot

template<class T>
void Tree<T>::nodeSaveAsDot(std::ofstream &file, const TreeNode<T> *parent) const {

    if (parent == nullptr)
        return;

    if (parent->getLeft() != nullptr)
        file << parent->getKey() << " -> " << parent->getLeft()->getKey() << ";" << std::endl;
    if (parent->getRight() != nullptr)
        file << parent->getKey() << " -> " << parent->getRight()->getKey() << ";" << std::endl;

    file << parent->getKey() << " [label=\"" << parent->getInfo() << "\"];" << std::endl;


    if (parent->getLeft() != nullptr)
        nodeSaveAsDot(file, parent->getLeft());

    if (parent->getRight() != nullptr)
        nodeSaveAsDot(file, parent->getRight());

}

template<class T>
int Tree<T>::getSize() const {

    return size;

}

template<class T>
void Tree<T>::setSize(int size) {

    Tree::size = size;

}

#endif
