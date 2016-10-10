#ifndef expTree_h
#define expTree_h

#include "token.h"
#include "Tree.h"



class ExpTree : public Tree<Token>{

	public:
		/**
		* @function build
		* @abstract builds the expression tree from input
		* @param takes a string with the expression (in prefix-notation) to be placed in the tree
		* @return returns nothing
		* @pre none
		* @post the expressions are stored in an expression tree
		**/
		void build(std::string & expr);
		/**
		* @function simplify
		* @abstract simplifies the expression in the expression tree
		* @param does not take any parameters
		* @return returns nothing
		* @pre none
		* @post the expression in the expression tree is simplified
		**/
		void simplify();

    /**
    * @function evalDouble
    * @abstract evaluates the expression tree in x at at double
    * @param takes a double for the variable x
    * @return returns nothing
    * @pre none
    * @post all instances of x are repaced by the input, the result is a expression
            in the remaining variables
    **/
		void eval(double value);
		/**
		* @function diff
		* @abstract differentiates the expression tree with respect to x
		* @param does not take any parameters
		* @return returns nothing
		* @pre none
		* @post the expression is differentiated with respect to x
		**/
		void diff();
		/**
		* @function printInfix
		* @abstract stores the (infix) representation of the expression tree in an ostream
		* @param taken an ostream to store the representation expression tree in
		* @return returns nothing
		* @pre none
		* @post the expression tree is representated (in infix) in the given ostream
		**/
		void printInfix(std::ostream &out) const;

	protected:
		/**
		* @function parseRight
		* @abstract recursively adds the remaining expressions as a right child
		* @param takes the remaining string to convert, the word to add to the tree
					and a pointer to the node to add the child to
		* @return returns nothing
		* @pre none
		* @post the expression is added to the provided node as a right child
		**/
        void parse(std::string &subExpr, std::string &word, TreeNode<Token>* current, bool left);
		//void parseRight(std::string &subExpr, std::string &word, TreeNode<Token>* current);
		/**
		* @function parseLeft
		* @abstract recursively adds the remaining expressions as a left child
		* @param takes the remaining string to convert, the word to add to the tree
					and a pointer to the node to add the child to
		* @return returns nothing
		* @pre none
		* @post the expression is added to the provided node as a left child
		**/
		//void parseLeft(std::string &subExpr, std::string &word, TreeNode<Token>* current);
		/**
		* @function copySubtree
		* @abstract copies the intire subtree, including the subroot and retuns the root of the copied tree
		* @param takes a pointer to a node from which the subtree will be copied
		* @return returns the root pointer of the copied subtree
		* @pre none
		* @post there is now a copied subtree created 
		**/
		TreeNode<Token>* copySubtree(TreeNode<Token>* current);
		/**
		* @function simplifyNode
		* @abstract recursive function that simplifies a subtree 
		* @param takes a pointer to the root of the subtree to be simplified
		* @return returns a pointer to the root of the new simplified subtree
		* @pre none
		* @post the subree returned is now simplified
		**/
		TreeNode<Token>* simplifyNode(TreeNode<Token>* current);
		/**
		* @function evalIntNode
		* @abstract recursive function that evaluates a subtree in x at a given integer
		* @param takes a pointer to the root of the subtree and an integer to evaluate x in
		* @return returns nothing
		* @pre none
		* @post the subtree is evaluated at the given value
		**/
		void evalIntNode(TreeNode<Token>* current, int value);
		/**
		* @function evalDoubleNode
		* @abstract recursive function that evaluates a subtree for a given double
		* @param takes a pointer to the root of the subtree and a double to evaluate x in
		* @return returns nothing
		* @pre none
		* @post the subtree is evaluated for the given value
		**/
		void evalNode(TreeNode<Token> *current, double value);
		/**
		* @function diffNode
		* @abstract recursive function that differentiates a subtree
		* @param takes a pointer to the root of the subtree
		* @return returns nothing
		* @pre none
		* @post the expression in the subtree is differentiated
		**/		
		void diffNode(TreeNode<Token>* current);
		/**
		* @function printInfixNode
		* @abstract recursive function that stores the (infix) representation of the expression of the subtree in an ostream
		* @param taken an ostream to store the representation expression tree in and a pointer to the root of the subtree
		* @return returns nothing
		* @pre none
		* @post the expression in the subtree is representated (in infix) in the given ostream
		**/
		void printInfixNode(std::ostream &out, const TreeNode<Token>* current) const;

        const double PRECISION = 0.0000001;

    Token parseToken(std::string word);

    TreeNode<Token> *parse(std::string & expr);
};//ExpTree

#endif
