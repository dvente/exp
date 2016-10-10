#ifndef token_h
#define token_h

#include <string>

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

	bool isOperator() const;
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
