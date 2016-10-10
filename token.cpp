#include "token.h"
#include <iostream>

Token::Token(){

	type = UD;//undefined token, used only for debugging purposes

}//Token

bool Token::isBinaryOperator() const{

    return type == PLUS || type == MINUS || type == PRODUCT || type == DIVIDE || type == POW;

}//isBinaryOperator

bool Token::isNullary() const{

	return type == VARIABLE || type == NUMBER || type == PI;

}//isNullary

bool Token::isUnaryOperator() const{

	return type == SIN || type == COS;

}//isUnaryOperator

bool Token::isOperator() const{

    return isBinaryOperator() || isUnaryOperator();

}

std::ostream &operator<<(std::ostream &s, const Token &form){
	
	if(form.type == Token::NUMBER)
		s << form.number;
	if(form.type == Token::PI)
		s << "pi";
	if(form.type == Token::COS)
		s << "cos";
	if(form.type == Token::SIN)
		s << "sin";
	if(form.type == Token::PLUS)
		s << "+";
	if(form.type == Token::MINUS)
		s << "-";
	if(form.type == Token::VARIABLE)
		s << form.variable;
	if(form.type == Token::POW)
		s << "^";
	if(form.type == Token::PRODUCT)
		s << "*";
	if(form.type == Token::DIVIDE)
		s << "/";
	if(form.type == Token::UD)
		s << "UD";
	return s;
}//operator<<
