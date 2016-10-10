//
// Created by daniel on 10-10-16.
//

#include "StringOperations.h"
#include <algorithm>
#include <sstream>

bool stringIsBinaryOperator(const std::string subExpr) {

    return subExpr == "-" || subExpr == "+" || subExpr == "^" || subExpr == "*" || subExpr == "/";

}//isBinaryOperator

bool stringIsOperator(const std::string subExpr) {

    return stringIsBinaryOperator(subExpr) || subExpr == "sin" || subExpr == "cos";

}

bool stringIsUnaryOperator(const std::string subExpr) {

    return subExpr == "sin" || subExpr == "cos";

}//isUnaryOperator

bool extractFirstWord(std::string & original, std::string &word){

    std::string::size_type pos;
    std::istringstream iss(original);

    iss >> word;
    pos = original.find(word);

    if (pos != std::string::npos){//cursor is still not at the end of the string
        original.erase(pos, word.length());//remove the word we have found
        original.erase(0,1);//remove space at beginning of the string
        return true;
    }//if
    else //no word is found
        return false;

}//extractFirstWord

bool stringIsDouble(std::string input) {

    std::string::size_type pos;
    pos = input.find(".");

    return pos == std::string::npos; //decimal point not found, so it is not a double

}//isDouble

void toLower(std::string &data){

    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

}
