#ifndef token_h
#define token_h

#include <string>

/**
* @function isBinaryOperator
* @abstract determines whether or not the string is a binary operator
* @param takes a string
* @return returns true if the string is a binary operator and false if this is not the case
* @pre none
* @post nothing is changed
**/
bool isBinaryOperator(const std::string subExpr);
/**
* @function extractFirstWord
* @abstract extracts the first expression of the string
* @param takes the original string, a string to store the found word and a string to store the remaining part of the string
* @return returns true if it has found an expression and removed this word and false if there are no expressions left in the string
* @pre none
* @post 'word' now contains the first expression and 'target' contains the rest of the string (where the found word is removed) 
**/
bool extractFirstWord(std::string original, std::string &word, std::string &target );
/**
* @function isDouble
* @abstract determines whether or not the string is a double
* @param takes a string
* @return returns true if the string is a double and false if this is not the case
* @pre none
* @post nothing is changed
**/
bool isDouble(std::string input);
/**
* @function toLower
* @abstract fixes that the string contains only letters in lower case, so that it is no problem if you type it in upper case
* @param takes a string
* @return does not return anything
* @pre none
* @post the string only contains lower case letters
**/
void toLower(std::string &data);

struct Token {
	enum{
		PLUS, MINUS, NUMBER, VARIABLE, SIN, COS, POW, PRODUCT, DIVIDE, PI, UD
	} type;
	
	union{
	
		char variable;
		double number;
	
	};
	
	Token();
	/**
	* @function isBinaryOperator
	* @abstract determines whether or not the token is a binary operator
	* @param takes no parameters
	* @return returns true if the token is a binary operator and false if this is not the case
	* @pre none
	* @post nothing is changed
	**/
	bool isBinaryOperator() const;
	/**
	* @function isUnaryOperator
	* @abstract determines whether or not the token is a unary operator
	* @param takes no parameters
	* @return returns true if the token is a unary operator and false if this is not the case
	* @pre none
	* @post nothing is changed
	**/
	bool isUnaryOperator() const;
	/**
	* @function isNullary
	* @abstract determines whether or not the token is a nullary (variable or number)
	* @param takes no parameters
	* @return returns true if the token is a nullary and false if this is not the case
	* @pre none
	* @post nothing is changed
	**/
	bool isNullary() const;

};

/**
* @function operator<<
* @abstract defines the operator '<<'
* @param takes a token and a ostream
* @return returns an ostream
* @pre none
* @post nothing is changed
**/
std::ostream &operator<<(std::ostream &s, const Token &form);

#endif
