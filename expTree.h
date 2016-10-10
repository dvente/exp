#ifndef expTree_h
#define expTree_h

#include "token.h"
#include "Tree.h"

class ExpTree : public Tree<Token> {

public:

    void build(std::string &expr);
    void simplify();
    void eval(double value);
    void diff();
    void printInfix(std::ostream &out) const;

protected:

    const double PRECISION = 0.0000001;

    TreeNode<Token> *copySubtree(TreeNode<Token> *current);
    TreeNode<Token> *simplifyNode(TreeNode<Token> *current);
    bool equalSubtrees(TreeNode<Token> *left, TreeNode<Token> *right);
    void evalNode(TreeNode<Token> *current, double value);
    void diffNode(TreeNode<Token> *current);
    void printInfixNode(std::ostream &out, const TreeNode<Token> *current) const;
    TreeNode<Token> *parse(std::string &expr);

};//ExpTree

#endif
