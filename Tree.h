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

template <class T>
class Tree{
	public:
		/**
		* @function tree (constructor)
		* @abstract creates a tree object containing a pointer to the root
		* @param takes no parameters
		* @return does not return anything
		* @pre none
		* @post a object of class tree is created containing a pointer to the root
		**/
		Tree();

		/**
		* @function ~tree (destructor)
		* @abstract deletes the tree
		* @param takes no parameters
		* @return does not return anything
		* @pre none
		* @post a object of class tree is deleted and memory is free
		**/
		~Tree();
		
		/**
		* @function insert
		* @abstract inserts a new node in the tree on the left side
		* @param takes object of type T
		* @return returns a bool which is true iff the stack is empty
		* @pre a stack must exist 
		* @post tree now contains a leaf with object
		**/
		bool insert(T info);
		
		/**
		* @function contains
		* @abstract checks if the tree contains a node with object of type T
		* @param takes object of type T
		* @return returns a bool which is true iff the tree contains a node with this object
		* @pre the tree must exist and be non-empty
		* @post nothing is changed
		**/
		bool contains(T info) const;
		
		/**
		* @function showpreorder
		* @abstract writes the nodes of the tree in preorder
		* @param takes no parameters 
		* @return returns nothing
		* @pre the tree must exist and not be empty
		* @post nothing is changed
		**/
		void showPreOrder(std::ostream &out) const;
		
		/**
		* @function showinorder
		* @abstract writes the nodes of the tree in order
		* @param takes no parameters
		* @return returns nothing
		* @pre the tree must exist and not be empty
		* @post nothing is changed
		**/
		void showInOrder(std::ostream &out) const;

		/**
		* @function showpostorder
		* @abstract writes the nodes of the tree in postorder
		* @param takes no parameters
		* @return returns nothing
		* @pre the tree must exist and not be empty
		* @post nothing is changed
		**/
		void showPostOrder(std::ostream &out) const;
		
		/**
		* @function saveasdot
		* @abstract saves a file with all the nodes represented in it
		* @param takes no parameters
		* @return returns a bool which is true iff saving the file was succesfull
		* @pre a stack must exist and must not be emtpy
		* @post nothing is changed
		**/
		bool saveAsDot(std::string filename) const;

	int getSize() const;

	void setSize(int size);
	//amount of nodes, necessary to print DOT
	protected:
		TreeNode<T> *root; //variable for the root node
		/**
		* @function insertNode
		* @abstract recursive function that determines where the new treenode should be added and does so
		* @param takes the pointer to the current treenode of which the new treenode should be a child and the info of the new treenode
		* @return returns a bool which is true iff the treenode is inserted
		* @pre none
		* @post a new treenode is inserted
		**/
		bool insertNode(TreeNode<T>* current, T info);
		/**
		* @function nodeContains
		* @abstract recursive function that determines if the subtree contains a node with the given info
		* @param takes the info which the function is going to search for and the pointer to the rootnode of the subtree
		* @return returns a bool which is true iff the subtree contains the info
		* @pre none
		* @post nothing is changed
		**/
		bool nodeContains(T info, const TreeNode<T>* parent) const;
		/**
		* @function nodeShowInOrder
		* @abstract recursive function to represent the subtree in inorder
		* @param takes an ostream and a pointer to the rootnode of the subtree
		* @return returns nothing
		* @pre none
		* @post the info of the subtree is stored in inorder
		**/		
		void nodeShowInOrder(std::ostream &out, const TreeNode<T>* parent) const;
		/**
		* @function nodeShowPreOrder
		* @abstract recursive function to represent the subtree in preorder
		* @param takes an ostream and a pointer to the rootnode of the subtree
		* @return returns nothing
		* @pre none
		* @post the info of the subtree is stored in preorder
		**/
		void nodeShowPreOrder(std::ostream &out, const TreeNode<T>* parent) const;
		/**
		* @function nodeShowPostOrder
		* @abstract recursive function to represent the subtree in postorder
		* @param takes an ostream and a pointer to the rootnode of the subtree
		* @return returns nothing
		* @pre none
		* @post the info of the subtree is stored in postorder
		**/
		void nodeShowPostOrder(std::ostream &out, const TreeNode<T>* parent) const;
		/**
		* @function nodeSaveAsDot
		* @abstract saves a file with all the nodes of the subtree represented in it
		* @param takes an ofstream to save the file and a pointer to the rootnode of the subtree
		* @return returns nothing
		* @pre none
		* @post the nodes of the subtree are stored in file
		**/
		void nodeSaveAsDot(std::ofstream &file, const TreeNode<T>* parent) const;

	int size;

    void incSize();

    void decSize();
};

template <class T>
Tree<T>::Tree(){

	root = new TreeNode<T>;
	size = 0;

}//TreeNode::TreeNode 

template <class T>
Tree<T>::~Tree(){

	delete root;//recursively delete the tree

}//TreeNode::TreeNode

template <class T>
bool Tree<T>::nodeContains(T info, const TreeNode<T>* parent) const{

	if(info == parent->getInfo())
		return true;
	else{//not found so check children
		if (parent->getLeft() != NULL){
			if (nodeContains(info, parent->getLeft()))
				return true;
		}//if
		else if (parent->getRight() != NULL)
			return nodeContains(info, parent->getRight());
	}//else 

	return false;//children don't contain it, so return false

}//Tree:nodeContains

template <class T>
bool Tree<T>::insert(T info){

	return insertNode(root, info) && !contains(info);

}//Tree:insert

template <class T>
bool Tree<T>::insertNode(TreeNode<T>* current, T info){

	if(root == NULL){
		root = new TreeNode<T>;
		root->setInfo(info);
		root->setKey(1);
		size = 1;
		return true;
	}// if

	while(current->getLeft() != NULL)
		current = current->getLeft();

	TreeNode<T>* temp = new TreeNode<T>;
	current->setLeft(temp);
	temp->setInfo(info);
	temp->setKey(current->getKey() + 1);
	size++;
	return true;


}//Tree::inserNode

template <class T>
bool Tree<T>::contains(T info) const{
	if(root != NULL)
		return nodeContains(info, root);
	else
		return false;

}//Tree:Contains

template <class T>
void Tree<T>::nodeShowInOrder(std::ostream &out, const TreeNode<T>* parent) const{

	if(parent->getLeft() != NULL)
		nodeShowInOrder(out, parent->getLeft());
	
	out << parent->getInfo() << ", ";
	
	if(parent->getRight() != NULL)
		nodeShowInOrder(out, parent->getRight());

}//Tree::nodeShowInOrder

template <class T>
void Tree<T>::nodeShowPreOrder(std::ostream &out, const TreeNode<T>* parent) const{
	
	out << parent->getInfo() << ", ";

	if(parent->getLeft() != NULL)
		nodeShowPreOrder(out, parent->getLeft());
	
	if(parent->getRight() != NULL)
		nodeShowPreOrder(out, parent->getRight());

}//Tree::nodeShowPreOrder

template <class T>
void Tree<T>::nodeShowPostOrder(std::ostream &out, const TreeNode<T>* parent) const{

	if(parent->getLeft() != NULL)
		nodeShowPostOrder(out, parent->getLeft());
	
	if(parent->getRight() != NULL)
		nodeShowPostOrder(out, parent->getRight());

	out << parent->getInfo() << ", ";
	
}//Tree::nodeShowPostOrder

template <class T>
void Tree<T>::showInOrder(std::ostream &out) const{

	nodeShowInOrder(out, root);

}//Tree::showInOrder


template <class T>
void Tree<T>::showPreOrder(std::ostream &out) const{

	nodeShowPreOrder(out, root);

}//Tree::showPreOrder


template <class T>
void Tree<T>::showPostOrder(std::ostream &out) const{

	nodeShowPostOrder(out, root);

}//Tree::showPostOrder

template <class T>
bool Tree<T>::saveAsDot(const std::string filename) const{

	std::ofstream file;
	file.open(filename.c_str());
	
	if(file.is_open()){
	
		file << "digraph G {" << std::endl;
		nodeSaveAsDot(file, root);
		file << "}";
		file.close();
		return true;
	
	}//if 
	else
		return false;

}//Tree::saveAsDot

template <class T> void Tree<T>::nodeSaveAsDot(std::ofstream &file, const TreeNode<T>* parent) const{

	if(parent == NULL)
		return;

	if(parent->getLeft() != NULL)
		file << parent->getKey() << " -> " << parent->getLeft()->getKey() << ";" << std::endl;
	if( parent->getRight() != NULL)
		file << parent->getKey() << " -> " << parent->getRight()->getKey() << ";" << std::endl;
	
	file << parent->getKey() << " [label=\"" << parent->getInfo() << "\"];" << std::endl;
	 

	if(parent->getLeft() != NULL)
		nodeSaveAsDot(file, parent->getLeft());
	
	if(parent->getRight() != NULL)
		nodeSaveAsDot(file, parent->getRight());

}

template <class T> int Tree<T>::getSize() const {
	return size;
}

template <class T> void Tree<T>::setSize(int size) {
	Tree::size = size;
}
//Tree:nodeSaveAsDot

template <class T> void Tree<T>::incSize(){
    size++;
}

template <class T> void Tree<T>::decSize(){
    size--;
}

#endif
