#include "token.h"
#include <algorithm>
#include <sstream>
#include <iostream>

bool isBinaryOperator(const std::string subExpr) {

	if(subExpr == "-" || subExpr == "+" || subExpr == "^" || subExpr == "*" || subExpr == "/")
		return true;
	else
		return false;
}//isBinaryOperator

bool extractFirstWord(std::string original, std::string &word, std::string &target ){

	std::string::size_type pos;
	std::istringstream iss(original);
	target = original;

	iss >> word;
	pos = original.find(word);

	if (pos != std::string::npos){//cursor is still not at the end of the string
		target.erase(pos, word.length());//remove the word we have found
		target.erase(0,1);//remove space at beginning of the string
		return true;
	}//if 
	else //no word is found
		return false;

}//extractFirstWord

bool isDouble(std::string input){

	std::string::size_type pos;
	pos = input.find(".");

	if(pos == std::string::npos) //decimal point not found, so it is not a double
		return false;
	else 
		return true;

}//isDouble

void toLower(std::string &data){

	std::transform(data.begin(), data.end(), data.begin(), ::tolower);

}


Token::Token(){

	type = UD;//undefined token, used only for debugging purposes

}//Token

bool Token::isBinaryOperator() const{

	if(type == PLUS || type == MINUS || type == PRODUCT || type == DIVIDE || type == POW)
		return true;
	else 
		return false;

}//isBinaryOperator

bool Token::isNullary() const{

	if(type == VARIABLE || type == NUMBER )
		return true;
	else 
		return false;

}//isNullary

bool Token::isUnaryOperator() const{

	if(type == SIN || type == COS)
		return true;
	else 
		return false;

}//isUnaryOperator

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
