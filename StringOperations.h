//
// Created by daniel on 10-10-16.
//

#ifndef EXP_STRINGOPERATIONS_H
#define EXP_STRINGOPERATIONS_H
#include <string>

bool isOperator(const std::string subExpr);
bool isUnaryOperator(const std::string subExpr);

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
    bool splitOffFirstWord(std::string original, std::string &word, std::string &target );

bool extractFirstWord(std::string & original, std::string &word);
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



#endif //EXP_STRINGOPERATIONS_H
