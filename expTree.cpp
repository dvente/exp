#include "expTree.h"
#include "StringOperations.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>

void ExpTree::printInfix(std::ostream &out) const{ //call function on root

	printInfixNode(out, root);
	out << std::endl;

}//printInfix

void ExpTree::printInfixNode(std::ostream &out, const TreeNode<Token>* current) const{ //in order tree traversal

	if(current->getInfo().isBinaryOperator()) //output a parenthesis for operator
		out << "(";

	if(current->getLeft() != nullptr )
		printInfixNode(out, current->getLeft());
	
	out << current->getInfo();

	if(current->getInfo().isUnaryOperator())
		out << "(";
	
	if(current->getRight() != nullptr)
		printInfixNode(out, current->getRight());

	if(current->getInfo().isBinaryOperator() || current->getInfo().isUnaryOperator())
		out << ")";
}

void ExpTree::diffNode(TreeNode<Token>* current){ //recursive function to differentiate

	if(current == NULL)//recursion guard
		return;

	Token temp;//var to set info

	if(current->getInfo().type == Token::NUMBER || current->getInfo().type == Token::PI){//constants have derivative 0
	
		temp.number = 0;
		temp.type = Token::NUMBER;
		current->setInfo(temp);
	
	}//number derivative

	if(current->getInfo().type == Token::VARIABLE){//differentiating w.r.t. x so that has derivative 1 others have 0
		
		temp.type = Token::NUMBER;
		
		if(current->getInfo().variable == 'x')
			temp.number = 1;
		else
			temp.number = 0;

		current->setInfo(temp);
	}//variable derivative

	if(current->getInfo().type == Token::PLUS || current->getInfo().type == Token::MINUS){//derivative of sum is sum of derivatives
	
		diffNode(current->getRight());
		diffNode(current->getLeft());
	
	}//sum rule

	if(current->getInfo().type == Token::PRODUCT){//product rule d(fg) = d(f)g + fd(g)
	
		current->setRight(copySubtree(current)); //copy subtrees to differentiate
		current->setLeft(copySubtree(current->getRight()));

		temp.type = Token::PLUS;//set plus in current
		current->setInfo(temp);

		diffNode(current->getRight()->getRight());//differentiate the correct subtrees
		diffNode(current->getLeft()->getLeft());
	
	}//product rule

	if(current->getInfo().type == Token::SIN){//derivative of sin

		current->setRight(copySubtree(current));
		temp.type = Token::PRODUCT;
		current->setInfo(temp);
		
		current->setLeft(copySubtree(current->getRight()->getRight()));//chain rule
		diffNode(current->getLeft());
		
		temp.type = Token::COS;
		current->getRight()->setInfo(temp);
	
	}//sin
	
	if(current->getInfo().type == Token::COS){//derivative of cos
	
		current->setRight(copySubtree(current)); //copy subtree
		TreeNode<Token>* left = new TreeNode<Token>; //extra node is needed for the extra * -1
		current->setLeft(left);
		size++; //set tree size for dot
		current->getLeft()->setKey(size);
		temp.type = Token::NUMBER;
		temp.number = -1;
		current->getLeft()->setInfo(temp);
		
		temp.type = Token::PRODUCT;
		current->setInfo(temp);

		current->getRight()->setRight(copySubtree(current->getRight()));//copy subtree to the correct place
		current->getRight()->setLeft(copySubtree(current->getRight()->getRight()->getRight()));
		diffNode(current->getRight()->getLeft()); //chain rule
		current->getRight()->setInfo(temp);

		temp.type = Token::SIN;
		current->getRight()->getRight()->setInfo(temp);

	}//cos

	if(current->getInfo().type == Token::POW){ //power
		current->setLeft(copySubtree(current));//copy relevant subtrees
		current->setLeft(copySubtree(current));
		temp.type = Token::NUMBER;
		temp.number = current->getRight()->getInfo().number - 1; //d(x^C)=x^{C-1}*C
		current->getLeft()->getLeft()->getRight()->setInfo(temp);

		temp.type = Token::PRODUCT;
		current->setInfo(temp);
		current->getLeft()->setInfo(temp);
		current->setRight(copySubtree(current->getLeft()->getLeft()->getLeft()));
		
		diffNode(current->getRight());

	}//POW

	if(current->getInfo().type == Token::DIVIDE){//d(f/g)=(d(f)*g-f*d(g))/(g^2)
		
		current->setLeft(copySubtree(current));

		current->getLeft()->setLeft(copySubtree(current->getLeft()));//copy relevant subtrees
		current->getLeft()->setRight(copySubtree(current->getLeft()->getLeft()));

		current->getRight()->setLeft(copySubtree(current->getRight()));
		temp.type = Token::NUMBER;
		temp.number = 2;
		TreeNode<Token>* right = new TreeNode<Token>; //new nodes are needed so create them and set them appropriately
		current->getRight()->setRight(right);
		size++;
		current->getRight()->getRight()->setKey(size);
		current->getRight()->getRight()->setInfo(temp);

		temp.type = Token::POW;
		current->getRight()->setInfo(temp);

		temp.type = Token::MINUS;
		current->getLeft()->setInfo(temp);

		temp.type = Token::PRODUCT;
		current->getLeft()->getLeft()->setInfo(temp);
		current->getLeft()->getRight()->setInfo(temp);

		diffNode(current->getLeft()->getLeft()->getLeft()); //differentiate the subtrees
		diffNode(current->getLeft()->getRight()->getRight());

	}//DIVIDE

}//diffNode

void ExpTree::diff(){//call the function on the root

	diffNode(root);
	simplify();

}//diff

void ExpTree::evalNode(TreeNode<Token> *current, double value){//evaluates the expression in a double

	if(current == NULL)
		return;

    evalNode(current->getRight(), value);
    evalNode(current->getLeft(), value);

	Token temp;

	if(current->getInfo().type == Token::VARIABLE && current->getInfo().variable == 'x'){
		temp.type = Token::NUMBER;
		temp.number = value;
		current->setInfo(temp);
	}// var == x 

}//evalNode


void ExpTree::eval(double value){//function call

    evalNode(root, value);
	simplify();

}//eval
 
 
void ExpTree::simplify(){ //function call

	root = simplifyNode(root);

}//simplfy

TreeNode<Token>* ExpTree::simplifyNode(TreeNode<Token>* current){
	
	if(current == NULL)//recursion guard
		return NULL;

	bool change = false; //used to not terminate the function prematurely

	current->setRight(simplifyNode(current->getRight()));//first simplify the children
	current->setLeft(simplifyNode(current->getLeft()));
	
	Token temp;//used to set temp

	if(current->getInfo().isBinaryOperator()){
		
		if(current->getRight()->getInfo().type == Token::VARIABLE &&
		 current->getLeft()->getInfo().type == Token::VARIABLE){//both children are variables
			if(current->getRight()->getInfo().variable == current->getLeft()->getInfo().variable){
				if(current->getInfo().type == Token::MINUS){//x-x
					temp.type = Token::NUMBER;
					temp.number = 0;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
				}//x-x
				if(current->getInfo().type == Token::DIVIDE){//x/x
					temp.type = Token::NUMBER;
					temp.number = 1;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
				}//x/x
			}//children have same variable

			return current;
		
		}//two variable children

		if(current->getRight()->getInfo().type == Token::NUMBER){
			
			if(current->getRight()->getInfo().number < PRECISION 
			&& current->getRight()->getInfo().number > double(-1)*PRECISION){//right child is 0
				if(current->getInfo().type == Token::PLUS 
				|| current->getInfo().type == Token::MINUS){//adding or subtracting zero
					delete current->getRight();//free memory
					current->setRight(NULL);
					change = true;
					return current->getLeft();
				}//adding zero
				
				else if(current->getInfo().type == Token::PRODUCT){//multiply by zero
					temp.type = Token::NUMBER;
					temp.number = 0;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//multiply by zero

				else if (current->getInfo().type == Token::POW){//E^0
					temp.type = Token::NUMBER;
					temp.number = 1;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//E^0
				else if (current->getInfo().type == Token::DIVIDE){//E/0
					std::cout << "division by 0...\n(dumbass)\n";
					exit(EXIT_FAILURE);
				}//E/0
				if(change)
					return current;
			}//rightchild is 0

			if(current->getRight()->getInfo().number - 1 < PRECISION && 
			current->getRight()->getInfo().number - 1 > double(-1)*PRECISION){//right child is 1
				
				if(current->getInfo().type == Token::PRODUCT){//multiply by 1
					delete current->getRight();//free memory
					current->setRight(NULL);
					change = true;
					return current->getLeft();
				}//multiply by 1

				else if (current->getInfo().type == Token::POW){//E^1
					delete current->getRight();//free memory
					current->setRight(NULL);
					change = true;
					return current->getLeft();
				}//E^1
				
				else if (current->getInfo().type == Token::DIVIDE){//E/1
					delete current->getRight();//free memory
					current->setRight(NULL);
					change = true;
					return current->getLeft();
				}//E/1

				if(change) //nothing changed so continue
					return current;

			}//rightchild is 1

		}//if
		if(current->getLeft()->getInfo().type == Token::NUMBER){
			if(current->getLeft()->getInfo().number < PRECISION && 
			current->getLeft()->getInfo().number > double(-1)*PRECISION){//left child is 0

				if(current->getInfo().type == Token::PLUS){//adding zero
					current->setInfo(current->getRight()->getInfo());
					delete current->getLeft();
					current->setLeft(NULL);
					change = true;
					return current->getRight();
				}//adding zero

				if(current->getInfo().type == Token::MINUS ){//subtracting from zero
					if(current->getRight()->getInfo().type == Token::NUMBER 
						|| current->getRight()->getInfo().type == Token::PI){
							temp = current->getRight()->getInfo();
							temp.number = temp.number*-1;
							current->getRight()->setInfo(temp);
							delete current->getLeft();
							current->setLeft(NULL);
							change = true;
							return current->getRight();
						}//if number
						else{
							temp.type = Token::PRODUCT;
							current->setInfo(temp);
							temp.type = Token::NUMBER;
							temp.number = -1;
							current->getLeft()->setInfo(temp);
						}// 0-E
				}//adding zero
				
				else if(current->getInfo().type == Token::PRODUCT){//multiply by zero
					temp.type = Token::NUMBER;
					temp.number = 0;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//multiply by zero

				else if (current->getInfo().type == Token::POW){//0^E (E is not 0)
					temp.type = Token::NUMBER;
					temp.number = 0;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//E^0
				else if (current->getInfo().type == Token::DIVIDE){//0/E
					temp.type = Token::NUMBER;
					temp.number = 0;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//0/E

				if(change)//nothing is changed so continue
					return current;

			}//left child is 0
			if((current->getLeft()->getInfo().number - 1) < PRECISION &&
			 (current->getLeft()->getInfo().number - 1) > double(-1)*PRECISION){//left child is 1
				
				if(current->getInfo().type == Token::PRODUCT){//multiply by 1
				
					delete current->getLeft();
					current->setLeft(NULL);
					change = true;
					return current->getRight();
				}//multiply by 1

				else if (current->getInfo().type == Token::POW){//1^E 
					temp.type = Token::NUMBER;
					temp.number = 1;
					current->setInfo(temp);
					delete current->getRight();//free memory
					delete current->getLeft();
					current->setRight(NULL);
					current->setLeft(NULL);
					change = true;
				}//1^E

				if(change)
					return current;

			}//Left child is 1
		}//if
		
		if((current->getRight()->getInfo().type == Token::NUMBER && current->getLeft()->getInfo().type == Token::NUMBER) ||
		(current->getRight()->getInfo().type == Token::PI && current->getLeft()->getInfo().type == Token::NUMBER) || 
		(current->getRight()->getInfo().type == Token::NUMBER && current->getLeft()->getInfo().type == Token::PI) || 
		(current->getRight()->getInfo().type == Token::PI && current->getLeft()->getInfo().type == Token::PI)){//has two number children so evaluate the expression
			temp.type = Token::NUMBER;
			if(current->getInfo().type == Token::MINUS){//parse for
				if(floor(current->getLeft()->getInfo().number) != current->getLeft()->getInfo().number || 
					floor(current->getRight()->getInfo().number) != current->getRight()->getInfo().number)//parse for doubles
						temp.number = double(current->getLeft()->getInfo().number) - double(current->getRight()->getInfo().number);
					else
						temp.number = current->getLeft()->getInfo().number - current->getRight()->getInfo().number;
				}
				else if(current->getInfo().type == Token::PLUS){
					if(floor(current->getLeft()->getInfo().number) != current->getLeft()->getInfo().number || 
					floor(current->getRight()->getInfo().number) != current->getRight()->getInfo().number)//parse for doubles
						temp.number = double(current->getLeft()->getInfo().number) + double(current->getRight()->getInfo().number);
					else
						temp.number = current->getLeft()->getInfo().number + current->getRight()->getInfo().number;
				}
				else if(current->getInfo().type == Token::POW){
					if(floor(current->getLeft()->getInfo().number) != current->getLeft()->getInfo().number || 
					floor(current->getRight()->getInfo().number) != current->getRight()->getInfo().number)//parse for doubles
						temp.number = pow(double(current->getLeft()->getInfo().number), double(current->getRight()->getInfo().number));
					else
						temp.number = pow(current->getLeft()->getInfo().number, current->getRight()->getInfo().number);
				}  
				else if(current->getInfo().type == Token::PRODUCT){
					if(floor(current->getLeft()->getInfo().number) != current->getLeft()->getInfo().number || 
					floor(current->getRight()->getInfo().number) != current->getRight()->getInfo().number)//parse for doubles
						temp.number = double(current->getLeft()->getInfo().number) * double(current->getRight()->getInfo().number);
					else
						temp.number = current->getLeft()->getInfo().number * current->getRight()->getInfo().number;
				}  
				else if(current->getInfo().type == Token::DIVIDE){//
					if((current->getLeft()->getInfo().number < current->getRight()->getInfo().number) || 
						(floor(current->getLeft()->getInfo().number) != current->getLeft()->getInfo().number) || 
						(floor(current->getRight()->getInfo().number) != current->getRight()->getInfo().number))//parse for doubles and divisiblity
						temp.number = double(current->getLeft()->getInfo().number) / double(current->getRight()->getInfo().number);
					else
						temp.number = current->getLeft()->getInfo().number / current->getRight()->getInfo().number;


				} 

				current->setInfo(temp); //set the answer
				delete current->getRight();
				delete current->getLeft();//free memory
				current->setRight(NULL);
				current->setLeft(NULL);
		}//children are numbers

	}//binary
	else if(current->getInfo().isUnaryOperator() 
	&& (current->getRight()->getInfo().type == Token::NUMBER ||
	 current->getRight()->getInfo().type == Token::PI)){//has a singel (right) child
		
		temp.type = Token::NUMBER;

		if(current->getInfo().type == Token::COS)//cos
			temp.number = cos(current->getRight()->getInfo().number);
		else //sin
			temp.number = sin(current->getRight()->getInfo().number);	
			
		delete current->getRight();//free memory
		current->setRight(NULL);
		current->setInfo(temp);


	}//unary
		
	return current;

}//

TreeNode<Token>* ExpTree::copySubtree(TreeNode<Token>* current){
	
   if (current == NULL) //base case to end recursion when at tree end
        return NULL;

    //create the node and set the new key to original
    TreeNode<Token>* copy = new TreeNode<Token>;
    size++; //used for dot
    copy->setInfo(current->getInfo());
    copy->setKey(size);
    
    //just call recursively to copy the subtrees:
    copy->setLeft(copySubtree(current->getLeft()));
    copy->setRight(copySubtree(current->getRight()));

    return copy;

}//copySubtree

void ExpTree::build(std::string & expr){//build the expression tree from the root

    root = parse(expr);

}

Token ExpTree::parseToken(std::string word) {
	Token temp;

	if(word.length() > 1){
		if(word[0] == '-' || word[0] == '+' ||isdigit(word[0])){
			temp.type = Token::NUMBER;

			if(isDouble(word))
				temp.number = atof(word.c_str());
			else
				temp.number = atoi(word.c_str());
			return temp;
		}//if
		else if(word == "pi"){
			temp.type = Token::PI;
			temp.number = 3.14159265359;
			return temp;
		}//else if pi
		else if(word == "sin"){
			temp.type = Token::SIN;
			return temp;
		}//else if sin
		else if(word == "cos"){
			temp.type = Token::COS;
			return temp;
		}//else if cos
	}//if
	else{
        if(word==""){
            temp.type = Token::UD;
            return temp;
        }
		else if(isdigit(word[0])){
			temp.type = Token::NUMBER;
			temp.number = atoi(word.c_str());
			return temp;
		}//if is digit
		else if(isalpha(word[0])){
			temp.type = Token::VARIABLE;
			temp.variable = word[0];
			return temp;
		}//if is alpha

		else if(isBinaryOperator(word)){

			if(word == "-"){
				temp.type = Token::MINUS;
				return temp;
			}//if -
			else if(word == "+"){
				temp.type = Token::PLUS;
				return temp;
			}//if +
			else if(word == "^"){
				temp.type = Token::POW;
				return temp;
			}// if ^
			else if(word == "*"){
				temp.type = Token::PRODUCT;
				return temp;
			}// if *
			else if(word == "/"){
				temp.type = Token::DIVIDE;
				return temp;
			}//if /
		}//else if is binary operator
        else{//invalid input
            temp.type = Token::UD;
            return temp;
        }
	}//else
}

TreeNode<Token> *ExpTree::parse(std::string & expr) {

    if(expr=="")
        return nullptr;

    TreeNode<Token>* current = new TreeNode<Token>;
    size++;
    current->setKey(size);
    std::string word;
    Token token;

    extractFirstWord(expr,word);
    token = parseToken(word);
    current->setInfo(token);

    if(token.isNullary())
        return current;

    else if(token.isBinaryOperator()){
        current->setLeft(parse(expr));
        current->setRight(parse(expr));

    }else
        current->setRight(parse(expr));

    return current;
}

//TODO setup rules for when you find a UD