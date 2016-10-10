#include "token.h"
#include "StringOperations.h"
#include <iostream>

Token::Token(){

	type = UD;//undefined token, used only for debugging purposes

}//Token

bool Token::isAlbean() const {
    return type == PLUS || type == PRODUCT;
}

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

bool Token::isConstant() const {
    return type == Token::NUMBER || type == Token::PI;
}

bool Token::operator==(const Token &rhs) const {

    if (type == rhs.type) {
        if (type == VARIABLE)
            return variable == rhs.variable;
        else
            return !isConstant() || (number - rhs.number) < PRECISION;
    } else
        return false;
}

Token &Token::operator=(const Token &other) {

    type = other.type;
    if (type == NUMBER)
        number = other.number;
    else if (type == VARIABLE)
        variable = other.variable;

    return *this;
}

//Token& Token::operator=(Token arg)
//{
//    swap(arg);
//    return *this;
//}

bool Token::operator!=(const Token &rhs) const {
    return !(rhs == *this);
}

void Token::parse(std::string word) {

    if (word.length() > 1) {
        if (word[0] == '-' || word[0] == '+' || isdigit(word[0])) {
            type = Token::NUMBER;

            if (stringIsDouble(word))
                number = atof(word.c_str());
            else
                number = atoi(word.c_str());
        }//if
        else if (word == "pi") {
            type = Token::PI;
            number = 3.14159265359;

        }//else if pi
        else if (word == "sin") {
            type = Token::SIN;
        }//else if sin
        else if (word == "cos") {
            type = Token::COS;
        }//else if cos
    }//if
    else {
        if (word == "") {
            type = Token::UD;
        } else if (isdigit(word[0])) {
            type = Token::NUMBER;
            number = atoi(word.c_str());
        }//if is digit
        else if (isalpha(word[0])) {
            type = Token::VARIABLE;
            variable = word[0];
        }//if is alpha

        else if (stringIsBinaryOperator(word)) {

            if (word == "-") {
                type = Token::MINUS;
            }//if -
            else if (word == "+") {
                type = Token::PLUS;
            }//if +
            else if (word == "^") {
                type = Token::POW;
            }// if ^
            else if (word == "*") {
                type = Token::PRODUCT;
            }// if *
            else if (word == "/") {
                type = Token::DIVIDE;
            }//if /
        }//else if is binary operator
        else {//invalid input
            type = Token::UD;
        }
    }//else
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
